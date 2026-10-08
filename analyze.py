#!/usr/bin/env python3
"""Analyse aller Kursblöcke mit Lizard und Cppcheck; Ausgabe als Markdown."""
import argparse
import datetime
import re
import shutil
import subprocess
from pathlib import Path
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parent

# Auswertung der eigentlichen Beispiele; zusätzliche Implementierungen und
# Testprogramme werden separat ausgewiesen und verzerren den Vergleich nicht.
AUXILIARY_FILES = {'alternative.c', 'test_comparison.c', 'test.c'}

BLOCK_FOCUS = {
    '01': 'Grundlagen: Die Cppcheck-Befunde sollten anhand der konkreten Bedingung geprüft werden.',
    '02': 'Code Smells: Zusätzlich zu Kennzahlen sind Verantwortlichkeiten und Lesbarkeit zu beurteilen.',
    '03': 'Namen und Datentypen: Das Lernziel ist Ausdruckskraft, nicht die Reduktion der Kontrollflusskomplexität.',
    '04': 'Funktionen: Die Verteilung von Verantwortung auf kleinere Funktionen ist fachlich zu beurteilen.',
    '05': 'Kontrollfluss: Eine Änderung der Verschachtelung kann auch bei gleicher CCN relevant sein.',
    '06': 'Metriken: Alternative Implementierung und Vergleichstest werden gesondert ausgewiesen.',
    '07': 'Testbarkeit: Die Trennung von Logik und Ein-/Ausgabe sowie automatisierte Tests sind entscheidend; CCN allein misst dies nicht.',
    '08': 'Refactoring: Verhaltensgleichheit und verständliche Verantwortlichkeiten sind neben Strukturmetriken zu prüfen.',
}


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
    for block in sorted((root / 'blocks').iterdir()):
        if not block.is_dir() or (block_filter and not block.name.startswith(block_filter)):
            continue
        for variant in ('dirty', 'clean'):
            folder = block / variant
            if not folder.is_dir():
                continue
            sources=sorted(folder.glob('*.c'))
            primary=[p for p in sources if p.name not in AUXILIARY_FILES]
            auxiliary=[p for p in sources if p.name in AUXILIARY_FILES]
            if not primary: continue
            functions=[]
            for source in primary:
                analysis=lizard.analyze_file(str(source))
                for f in analysis.function_list:
                    functions.append({'name':f.name,'file':source.name,'nloc':f.nloc,'ccn':f.cyclomatic_complexity,'params':f.parameter_count})
            result=execute(['cppcheck','--enable=warning,style,performance,portability','--xml','--xml-version=2','--quiet',*[str(p) for p in primary]])
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
            records.append({'variant':variant,'block':block.name,'files':len(primary),'auxiliary':auxiliary,'functions':functions,'issues':issues,'nesting':max((approximate_max_nesting(source) for source in primary),default=0)})
    return records

def display_block_name(name):
    """Repariert bekannte fehlerhafte Verzeichnisnamen nur in der Ausgabe."""
    return name.replace('SoftwarequalitÔö£├▒t', 'Softwarequalität')

def metrics(record):
    functions = record['functions']
    return {
        'nloc': sum(f['nloc'] for f in functions),
        'ccn': max((f['ccn'] for f in functions), default=0),
        'nesting': record['nesting'],
        'functions': len(functions),
        'params': max((f['params'] for f in functions), default=0),
        'issues': len(record['issues']),
    }


def signed_change(old, new):
    change = new - old
    return f'{change:+d}' if change else '0'


def didactic_interpretation(block, variants):
    """Verbindet die tatsächlich gemessenen Werte mit dem Lernziel des Blocks."""
    number = block.split('-')[0]
    focus = BLOCK_FOCUS.get(number, 'Die Ergebnisse müssen am Quellcode bewertet werden.')
    if 'dirty' not in variants or 'clean' not in variants:
        return 'Kein vollständiges dirty/clean-Paar vorhanden. ' + focus

    old, new = metrics(variants['dirty']), metrics(variants['clean'])
    changes = []
    for key, label in (
        ('ccn', 'maximale CCN'),
        ('nesting', 'heuristische maximale Verschachtelung'),
        ('functions', 'Funktionsanzahl'),
        ('nloc', 'Summe NLOC'),
        ('issues', 'Cppcheck-Meldungen'),
    ):
        before, after = old[key], new[key]
        if before == after:
            change = 'bleibt bei'
            changes.append(f'die {label} {change} {before}')
        else:
            changes.append(f'die {label} verändert sich von {before} auf {after}')
    sentence = '; '.join(changes)
    return sentence[0].upper() + sentence[1:] + '. ' + focus


def report(records):
    lines = [
        '# Qualitätsanalyse – Clean-Code-Kurs', '',
        f'Erstellt: {datetime.datetime.now().astimezone().isoformat(timespec="seconds")}', '',
        '## Messumfang', '',
        'Verglichen wird der eigentliche Beispielcode. Dateien `test.c`, `test_comparison.c` '
        'und `alternative.c` werden aus den dirty/clean-Metriken ausgeschlossen. '
        'Zusätzliche Implementierungen und Tests werden separat aufgeführt. '
        'Cppcheck analysiert ebenfalls nur die Vergleichsdateien; der Bericht prüft keine Tests.', '',
        '## Vergleich der Blöcke', '',
        '| Block | Variante | C-Dateien | Funktionen | Summe NLOC | Max. CCN | Verschachtelung (heur.) | Max. Parameter | Cppcheck-Meldungen |',
        '|---|---|---:|---:|---:|---:|---:|---:|---:|',
    ]
    for record in sorted(records, key=lambda r: (r['block'], r['variant'])):
        m = metrics(record)
        lines.append(
            f"| {record['block']} | {record['variant']} | {record['files']} | "
            f"{m['functions']} | {m['nloc']} | {m['ccn']} | "
            f"{m['nesting']} | {m['params']} | {m['issues']} |"
        )
    lines += [
        '',
        '**Interpretation:** NLOC zählt nichtleere Codezeilen in erkannten Funktionen. '
        'CCN ist die zyklomatische Komplexität; die Verschachtelung ist eine '
        'vereinfachte, nicht normierte Klammer-Heuristik, die pro Quelldatei berechnet '
        'und als Maximum über die Vergleichsdateien aggregiert wird. '
        'CCN-Maximalwerte und Parameter-Maximalwerte beziehen sich auf einzelne Funktionen; '
        'NLOC und Funktionsanzahl sind Summen über erkannte Funktionen. '
        'Die Aggregationsebenen unterscheiden sich. Weniger ist nicht automatisch besser.', '',
        '## Veränderung dirty → clean', '',
        '| Block | Δ Funktionen | Δ NLOC | Δ Max. CCN | Δ Verschachtelung | Δ Cppcheck |',
        '|---|---:|---:|---:|---:|---:|',
    ]
    by_block = {}
    for record in records:
        by_block.setdefault(record['block'], {})[record['variant']] = record
    for block, variants in sorted(by_block.items()):
        if 'dirty' not in variants or 'clean' not in variants:
            continue
        old, new = metrics(variants['dirty']), metrics(variants['clean'])
        lines.append(
            f"| {block} | {signed_change(old['functions'], new['functions'])} | "
            f"{signed_change(old['nloc'], new['nloc'])} | "
            f"{signed_change(old['ccn'], new['ccn'])} | "
            f"{signed_change(old['nesting'], new['nesting'])} | "
            f"{signed_change(old['issues'], new['issues'])} |"
        )
    lines += [
        '',
        '**Lesart:** Δ = clean − dirty. Negative Werte bedeuten eine Abnahme, '
        'nicht zwingend eine Qualitätsverbesserung. Bei Funktionszerlegung sind '
        'Maximalwerte und Summen nur eingeschränkt vergleichbar.', '',
        '## Didaktische Interpretation je Block', '',
    ]
    for block, variants in sorted(by_block.items()):
        lines.append(f"- **{block}:** {didactic_interpretation(block, variants)}")
    lines += ['', '## Separat ausgeschlossene Dateien', '']
    any_aux = False
    for record in sorted(records, key=lambda r: (r['block'], r['variant'])):
        if record['auxiliary']:
            any_aux = True
            names = ', '.join('`' + p.name + '`' for p in record['auxiliary'])
            lines.append(f"- **{record['block']} / {record['variant']}:** {names}")
    if not any_aux:
        lines.append('Keine zusätzlichen Dateien gefunden.')
    lines += [
        '',
        '## Funktionen mit der höchsten zyklomatischen Komplexität', '',
        '| Block | Variante | Funktion | Datei | NLOC | CCN | Parameter |',
        '|---|---|---|---|---:|---:|---:|',
    ]
    functions = sorted(
        ((r, f) for r in records for f in r['functions']),
        key=lambda pair: (-pair[1]['ccn'], -pair[1]['nloc'])
    )[:10]
    for record, func in functions:
        lines.append(
            f"| {record['block']} | {record['variant']} | `{func['name']}` | "
            f"`{func['file']}` | {func['nloc']} | {func['ccn']} | {func['params']} |"
        )
    lines += ['', '## Cppcheck-Befunde', '']
    for record in sorted(records, key=lambda r: (r['block'], r['variant'])):
        if not record['issues']:
            continue
        lines.append(f"### {display_block_name(record['block'])} – {record['variant']}")
        for issue in record['issues']:
            lines.append(
                f"- **{issue['severity']} / {issue['id']}** – "
                f"`{issue['file']}:{issue['line']}`: {issue['message']}"
            )
        lines.append('')
    if not any(r['issues'] for r in records):
        lines.append('Keine Meldungen in den gewählten Kategorien; dies beweist keine Fehlerfreiheit.')
    lines += [
        '', '## Testqualität und Coverage', '',
        '- Block 07 (clean): `make check` führt Tests aus; `make coverage` erzeugt einen gcov-Bericht.',
        '- Block 07 (dirty): keine automatisierte Testsuite; kein vergleichbarer Coverage-Wert.',
        '- Coverage zeigt Ausführung, nicht die Aussagekraft der Tests.',
        '', '## Grenzen der Messung', '',
        '- Cognitive Complexity wird nicht erhoben.',
        '- Heuristische Verschachtelung kann bei Makros und Kontrollstrukturen ohne Klammern abweichen.',
        '- Cppcheck-Meldungen hängen von Version, Konfiguration und Analyseumfang ab.',
        '- Die Analyse ermittelt keinen aggregierten Qualitätsscore.',
        '- Lesbarkeit, fachliche Korrektheit und Architekturqualität benötigen Reviews und Tests.',
        ''
    ]
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
