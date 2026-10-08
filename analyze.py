#!/usr/bin/env python3
"""Analyse aller Kursblöcke mit Lizard und Cppcheck; Ausgabe als Markdown."""
import argparse
import datetime
import re
import shutil
import subprocess
import sys
from pathlib import Path
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parent

def execute(args):
    result = subprocess.run(args, text=True, capture_output=True)
    return result

def approximate_max_nesting(source):
    """Heuristik für C: geschachtelte Kontrollblöcke mit geschweiften Klammern.

    Nicht geeignet als exakte Metrik bei Makros, mehrzeiligen Bedingungen
    oder Kontrollstrukturen ohne Klammern.
    """
    code = source.read_text(encoding='utf-8')
    code = re.sub(r'/\*.*?\*/|//[^\n]*', '', code, flags=re.S)
    code = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', '""', code)
    nesting = 0
    stack = []
    pending = False
    maximum = 0
    for line in code.splitlines():
        for token in re.findall(r'\b(?:if|for|while|switch|else|do)\b|[{};]', line):
            if token in ('if','for','while','switch','else','do'):
                pending = True
            elif token == '{':
                stack.append(pending)
                if pending:
                    nesting += 1
                    maximum = max(maximum, nesting)
                pending = False
            elif token == '}':
                if stack and stack.pop():
                    nesting -= 1
                pending = False
            elif token == ';':
                pending = False
    return maximum

def analyze(root, block_filter):
    import lizard
    # Die öffentliche Lizard-Funktion übernimmt die Erkennung der C-Sprache.
    # Die optionale Cognitive-Complexity-Erweiterung wird hier nicht erzwungen,
    # da die FileAnalyzer-API versionsabhängig ist.
    records=[]
    for variant in ('dirty','clean'):
        for folder in sorted((root/variant).iterdir()):
            if not folder.is_dir() or (block_filter and not folder.name.startswith(block_filter)):
                continue
            sources=sorted(folder.glob('*.c'))
            if not sources: continue
            functions=[]
            for source in sources:
                analysis=lizard.analyze_file(str(source))
                for f in analysis.function_list:
                    functions.append({'name':f.name,'file':source.name,'nloc':f.nloc,'ccn':f.cyclomatic_complexity,'params':f.parameter_count})
            result=execute(['cppcheck','--enable=warning,style,performance,portability','--xml','--xml-version=2','--quiet',*[str(p) for p in sources]])
            issues=[]
            try:
                tree=ET.fromstring(result.stderr)
                for error in tree.findall('.//error'):
                    location=error.find('location')
                    issues.append({'severity':error.get('severity',''), 'id':error.get('id',''), 'message':error.get('msg',''), 'file':Path(location.get('file','')).name if location is not None else '', 'line':location.get('line','') if location is not None else ''})
            except ET.ParseError as exc:
                raise RuntimeError(f'Cppcheck-XML ungültig für {folder}: {exc}') from exc
            if result.returncode not in (0,1):
                raise RuntimeError(f'Cppcheck fehlgeschlagen für {folder}: {result.stderr}')
            records.append({'variant':variant,'block':folder.name,'files':len(sources),'functions':functions,'issues':issues,'nesting':max((approximate_max_nesting(source) for source in sources),default=0)})
    return records

def display_block_name(name):
    """Repariert bekannte fehlerhafte Verzeichnisnamen nur in der Ausgabe."""
    return name.replace('SoftwarequalitÔö£├▒t', 'Softwarequalität')

def report(records):
    lines=['# Qualitätsanalyse – Clean-Code-Kurs','',f'Erstellt: {datetime.datetime.now().astimezone().isoformat(timespec="seconds")}', '', '## Vergleich der Blöcke','', '| Block | Variante | C-Dateien | Funktionen | Summe NLOC (Funktionen) | Max. CCN | Verschachtelung (heur.) | Max. Parameter | Cppcheck-Meldungen |','|---|---|---:|---:|---:|---:|---:|---:|---:|']
    for r in sorted(records,key=lambda x:(x['block'],x['variant'])):
        fs=r['functions']
        lines.append(f"| {r['block'].split(' - ')[0]} | {r['variant']} | {r['files']} | {len(fs)} | {sum(f['nloc'] for f in fs)} | {max((f['ccn'] for f in fs),default=0)} | {r['nesting']} | {max((f['params'] for f in fs),default=0)} | {len(r['issues'])} |")
    lines+=['','**Interpretation:** Die Verschachtelung ist eine vereinfachte, nicht normierte Klammer-Heuristik. NLOC zählt nichtleere Codezeilen innerhalb erkannter Funktionen, CCN ist die zyklomatische Komplexität. Die Maximalwerte gelten pro Funktion; die Funktionsanzahl kann sich zwischen Varianten unterscheiden. Weniger ist nicht automatisch besser. Cppcheck-Meldungen sind Prüfhinweise und müssen fachlich bewertet werden.','', '## Funktionen mit der höchsten zyklomatischen Komplexität','', '| Block | Variante | Funktion | Datei | NLOC | CCN | Parameter |','|---|---|---|---|---:|---:|---:|']
    funcs=sorted(((r,f) for r in records for f in r['functions']),key=lambda rf:(-rf[1]['ccn'],-rf[1]['nloc']))[:10]
    for r,f in funcs:
        lines.append(f"| {r['block'].split(' - ')[0]} | {r['variant']} | `{f['name']}` | `{f['file']}` | {f['nloc']} | {f['ccn']} | {f['params']} |")
    lines+=['','## Cppcheck-Befunde','']
    for r in sorted(records,key=lambda x:(x['block'],x['variant'])):
        if not r['issues']:continue
        lines.append(f"### {display_block_name(r['block'])} – {r['variant']}")
        for issue in r['issues']:
            lines.append(f"- **{issue['severity']} / {issue['id']}** – `{issue['file']}:{issue['line']}`: {issue['message']}")
        lines.append('')
    if not any(r['issues'] for r in records):lines.append('Keine Meldungen mit den gewählten Cppcheck-Kategorien. Dies ist kein Beweis für Fehlerfreiheit.')
    lines+=['','## Testqualität und Coverage','', '- Block 07 (clean): `make check` führt die Tests aus; `make coverage` erzeugt einen gcov-Bericht für `logic.c`.', '- Block 07 (dirty): keine automatisierte Testsuite. Ein numerischer Coverage-Vergleich wäre deshalb irreführend.', '- Coverage zeigt ausgeführte Zeilen/Zweige, aber nicht die Aussagekraft der Tests.','', '## Grenzen der Messung','', '- Der Bericht misst ausgewählte strukturelle Eigenschaften, nicht Lesbarkeit, fachliche Korrektheit oder Architekturqualität.','- Die Anzahl der Cppcheck-Meldungen hängt von Version, Konfiguration und Analyseumfang ab.','- Es wird bewusst kein aggregierter Qualitätsscore berechnet.','- Tests, Reviews und Architekturentscheidungen ergänzen die Analyse.','']
    return '\n'.join(lines)

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--block',help='Blocknummer, z. B. 06')
    parser.add_argument('--output',default='quality-report.md',help='Markdown-Ausgabepfad relativ zum Projekt')
    args=parser.parse_args()
    try:
        import lizard
    except ImportError:
        parser.error('Lizard fehlt: python3 -m pip install lizard')
    if not shutil.which('cppcheck'):
        parser.error('Cppcheck fehlt: apt-get install cppcheck')
    try:
        records=analyze(ROOT,args.block)
    except RuntimeError as exc:
        parser.error(str(exc))
    if not records:parser.error('Keine passenden C-Dateien gefunden')
    target=Path(args.output)
    if not target.is_absolute():target=ROOT/target
    target.parent.mkdir(parents=True,exist_ok=True)
    target.write_text(report(records),encoding='utf-8')
    print(f'Bericht erstellt: {target} ({len(records)} Varianten)')
if __name__=='__main__':main()
