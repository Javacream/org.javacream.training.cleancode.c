# Block 06 – Metriken und statische Codeanalyse

## Lernziel und Abgrenzung

Quantitative Metriken und statische Analysebefunde erheben, interpretieren und kritisch bewerten. Die Programmbeispiele zeigen bereits bekannte Verbesserungen; **neue Refactoring-Techniken werden hier nicht eingeführt**.

## Werkzeuge

- **Lizard:** NLOC (nichtleere Codezeilen je Funktion), zyklomatische Komplexität (CCN), Parameteranzahl.
- **Cppcheck:** Hinweise auf potenzielle Fehler und problematische C-Konstrukte.

Die Werkzeuge sind in der Devcontainer-Umgebung installiert.

## Durchführung

Vom Projektverzeichnis aus:

```sh
python3 analyze.py --block 06 --output resources/quality-report-block06.md
```

Alternativ in einem Verzeichnis von Block 06: `make metrics`.

Für alle acht Blöcke:

```sh
python3 analyze.py --output quality-report.md
```

Der Markdown-Bericht vergleicht `dirty` und `clean`, listet Funktionen nach Komplexität und zeigt Cppcheck-Befunde. **Die Werte sind tatsächliche Messungen**, keine beispielhaften Qualitätsnoten.

## Übung

1. Ermitteln Sie die Funktion mit der höchsten CCN und begründen Sie den Wert anhand der Kontrollflussentscheidungen.
2. Vergleichen Sie die Maximalwerte zwischen `dirty` und `clean`. Welche Rolle spielt die Aufteilung in mehrere Funktionen?
3. Untersuchen Sie jede Cppcheck-Meldung: Fehler, berechtigter Hinweis oder Fehlalarm?
4. Diskutieren Sie, warum eine niedrigere Kennzahl nicht zwingend verständlicheren Code bedeutet.
5. Benennen Sie Qualitätsaspekte, die weder Lizard noch Cppcheck messen können.

## Grenzen

Der Bericht ist **kein Qualitätsscore**. Weder Architekturentscheidungen noch semantische Verständlichkeit oder Testqualität lassen sich daraus zuverlässig ableiten. Compilerwarnungen, Tests und Reviews sind ergänzend erforderlich.
