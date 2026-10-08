# Block 06 – Metriken und statische Codeanalyse

## Lernziele
Nach diesem Block können die Teilnehmenden:
- mit den bereitgestellten Werkzeugen einen reproduzierbaren Qualitätsbericht erzeugen;
- CCN, NLOC, Parameteranzahl und die heuristische Verschachtelung für konkrete Funktionen interpretieren;
- mindestens zwei Implementierungen anhand von Messwerten **und** Quellcode-Lesbarkeit vergleichen;
- Cppcheck-Befunde zwischen möglichem Fehler, berechtigtem Hinweis und Fehlalarm unterscheiden;
- mindestens zwei Qualitätsaspekte nennen, die sich aus den Metriken nicht zuverlässig ableiten lassen.

## Fachlicher Hintergrund und Abgrenzung
Dieser Block führt **keine neuen Refactoring-Techniken** ein. Er untersucht die Aussagekraft von Messungen zu bereits bekannten Strukturverbesserungen.

- **Lizard:** NLOC, zyklomatische Komplexität (CCN) und Parameteranzahl. Cognitive Complexity wird in der aktuellen Kursumgebung nicht erhoben.
- **Kursskript:** zusätzliche, ausdrücklich **heuristische** Verschachtelungstiefe.
- **Cppcheck:** Hinweise auf potenzielle Fehler und problematische C-Konstrukte.

Ein Qualitätsbericht ist **kein allgemeiner Qualitätsscore**. Die Werkzeuge messen weder fachliche Verständlichkeit noch Architekturqualität oder Testgüte vollständig.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty`, `clean` und – soweit im Beispiel vorhanden – `alternative` in Block 06. Alle Varianten sollen dieselbe fachliche Risikobewertung liefern.

## Aufgabenstellung
1. Erzeugen Sie im Projektwurzelverzeichnis den Bericht:

```sh
python3 analyze.py --block 06 --output blocks/06-metriken/quality-report-block06.md
```

   Alternativ kann in `blocks/06-metriken/clean` `make metrics` verwendet werden. Für alle acht Blöcke: `python3 analyze.py --output quality-report.md`.
2. Identifizieren Sie die Funktion mit der höchsten CCN und erklären Sie den Wert anhand der Entscheidungen im Code.
3. Vergleichen Sie die Maximalwerte sowie einzelne Funktionen in `dirty` und `clean`; untersuchen Sie die Wirkung einer Funktionsaufteilung.
4. Führen Sie in `blocks/06-metriken/clean/` `make compare` aus (alternativ `make test`) und diskutieren Sie, ob eine niedrigere Kennzahl auch besser lesbaren Code bedeutet.
5. Klassifizieren Sie die relevanten Cppcheck-Meldungen und begründen Sie Ihre Einschätzung.
6. Vergleichen Sie auch Block 05: Eine gleichbleibende CCN kann mit geringerer kognitiver Belastung einhergehen.

## Erfolgskriterien
- Ein reproduzierbarer Markdown-Bericht liegt vor.
- Mindestens eine Funktion wird anhand von CCN und Kontrollfluss nachvollziehbar erläutert.
- Ein Vergleich zweier Varianten verbindet Messwerte mit einer eigenständigen Lesbarkeitsbeurteilung.
- Mindestens ein Analysebefund wird fachlich eingeordnet; Grenzen der Messung sind benannt.
- Die fachliche Risikobewertung der Varianten bleibt gleich.

## Reflexion
Welche Qualitätsentscheidung würden Sie **nicht** allein aufgrund eines Metrikwerts treffen? Welche zusätzlichen Informationen liefern Tests und Code Reviews?
