# Qualitätsanalyse – Clean-Code-Kurs

Erstellt: 2026-11-08T21:56:25+00:00

## Messumfang

Verglichen wird der eigentliche Beispielcode. Dateien `test.c`, `test_comparison.c` und `alternative.c` werden aus den dirty/clean-Metriken ausgeschlossen. Zusätzliche Implementierungen und Tests werden separat aufgeführt. Cppcheck analysiert ebenfalls nur die Vergleichsdateien; der Bericht prüft keine Tests.

## Vergleich der Blöcke

| Block | Variante | C-Dateien | Funktionen | Summe NLOC | Max. CCN | Verschachtelung (heur.) | Max. Parameter | Cppcheck-Meldungen |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| 01-grundlagen | clean | 1 | 2 | 16 | 2 | 1 | 2 | 0 |
| 01-grundlagen | dirty | 1 | 1 | 11 | 2 | 1 | 0 | 1 |
| 02-code-smells | clean | 1 | 2 | 20 | 5 | 0 | 4 | 0 |
| 02-code-smells | dirty | 1 | 2 | 23 | 6 | 0 | 4 | 0 |
| 03-namen-datentypen | clean | 1 | 1 | 26 | 16 | 1 | 1 | 1 |
| 03-namen-datentypen | dirty | 1 | 1 | 16 | 16 | 1 | 1 | 1 |
| 04-funktionen | clean | 1 | 5 | 24 | 3 | 1 | 2 | 0 |
| 04-funktionen | dirty | 1 | 2 | 16 | 5 | 1 | 6 | 0 |
| 05-kontrollfluss | clean | 1 | 2 | 15 | 8 | 1 | 4 | 0 |
| 05-kontrollfluss | dirty | 1 | 2 | 20 | 8 | 3 | 4 | 0 |
| 06-metriken | clean | 1 | 4 | 31 | 8 | 1 | 4 | 0 |
| 06-metriken | dirty | 1 | 3 | 29 | 11 | 2 | 4 | 0 |
| 07-testbarkeit | clean | 2 | 2 | 9 | 1 | 0 | 2 | 0 |
| 07-testbarkeit | dirty | 1 | 2 | 11 | 1 | 0 | 1 | 0 |
| 08-refactoring | clean | 2 | 5 | 26 | 4 | 0 | 5 | 0 |
| 08-refactoring | dirty | 2 | 2 | 18 | 7 | 2 | 5 | 0 |

**Interpretation:** NLOC zählt nichtleere Codezeilen in erkannten Funktionen. CCN ist die zyklomatische Komplexität; die Verschachtelung ist eine vereinfachte, nicht normierte Heuristik. Maximalwerte beziehen sich auf einzelne Funktionen. Weniger ist nicht automatisch besser.

## Veränderung dirty → clean

| Block | Δ Funktionen | Δ NLOC | Δ Max. CCN | Δ Verschachtelung | Δ Cppcheck |
|---|---:|---:|---:|---:|---:|
| 01-grundlagen | +1 | +5 | 0 | 0 | -1 |
| 02-code-smells | 0 | -3 | -1 | 0 | 0 |
| 03-namen-datentypen | 0 | +10 | 0 | 0 | 0 |
| 04-funktionen | +3 | +8 | -2 | 0 | 0 |
| 05-kontrollfluss | 0 | -5 | 0 | -2 | 0 |
| 06-metriken | +1 | +2 | -3 | -1 | 0 |
| 07-testbarkeit | 0 | -2 | 0 | 0 | 0 |
| 08-refactoring | +3 | +8 | -3 | -2 | 0 |

**Lesart:** Δ = clean − dirty. Negative Werte bedeuten eine Abnahme, nicht zwingend eine Qualitätsverbesserung. Bei Funktionszerlegung sind Maximalwerte und Summen nur eingeschränkt vergleichbar.

## Didaktische Interpretation je Block

- **01-grundlagen:** Grundlagen: Die Cppcheck-Warnung zur immer wahren Bedingung in dirty ist ein konkreter Diskussionsanlass.
- **02-code-smells:** Code Smells: Eine niedrigere CCN ist ein Indiz; Lesbarkeit und Verantwortlichkeiten sind zusätzlich zu beurteilen.
- **03-namen-datentypen:** Namen und Datentypen: Die CCN darf unverändert bleiben, weil hier nicht der Kontrollfluss verbessert werden soll.
- **04-funktionen:** Funktionen: Funktionszerlegung kann die maximale CCN senken und zugleich die Zahl der Funktionen erhöhen.
- **05-kontrollfluss:** Kontrollfluss: Geringere Verschachtelung bei gleicher CCN zeigt die Grenzen einer einzelnen Kennzahl.
- **06-metriken:** Metriken: Für den direkten dirty/clean-Vergleich zählt nur main.c; alternative.c und test_comparison.c werden separat ausgewiesen.
- **07-testbarkeit:** Testbarkeit: Eine höhere CCN der clean-Variante ist kein Gegenbeweis für bessere Testbarkeit; Tests und Coverage gesondert betrachten.
- **08-refactoring:** Refactoring: Die maximale CCN und die Verschachtelung können sinken, obwohl die Implementierung in mehr Funktionen aufgeteilt wird.

## Separat ausgeschlossene Dateien

- **06-metriken / clean:** `alternative.c`, `test_comparison.c`
- **07-testbarkeit / clean:** `test.c`
- **08-refactoring / clean:** `test.c`
- **08-refactoring / dirty:** `test.c`

## Funktionen mit der höchsten zyklomatischen Komplexität

| Block | Variante | Funktion | Datei | NLOC | CCN | Parameter |
|---|---|---|---|---:|---:|---:|
| 03-namen-datentypen | clean | `main` | `main.c` | 26 | 16 | 1 |
| 03-namen-datentypen | dirty | `main` | `main.c` | 16 | 16 | 1 |
| 06-metriken | dirty | `risk_score` | `main.c` | 17 | 11 | 4 |
| 05-kontrollfluss | dirty | `shipping_cost` | `main.c` | 15 | 8 | 4 |
| 06-metriken | clean | `incident_score` | `main.c` | 13 | 8 | 3 |
| 05-kontrollfluss | clean | `shipping_cost` | `main.c` | 10 | 8 | 4 |
| 08-refactoring | dirty | `calculate_order_total` | `logic.c` | 13 | 7 | 5 |
| 02-code-smells | dirty | `process` | `main.c` | 17 | 6 | 4 |
| 02-code-smells | clean | `process` | `main.c` | 14 | 5 | 4 |
| 04-funktionen | dirty | `process_order` | `main.c` | 11 | 5 | 6 |

## Cppcheck-Befunde

### 01-grundlagen – dirty
- **style / knownConditionTrueFalse** – `main.c:8`: Condition 'r>300' is always true

### 03-namen-datentypen – clean
- **style / constParameter** – `main.c:3`: Parameter 'argv' can be declared as const array

### 03-namen-datentypen – dirty
- **style / constParameter** – `main.c:2`: Parameter 'argv' can be declared as const array


## Testqualität und Coverage

- Block 07 (clean): `make check` führt Tests aus; `make coverage` erzeugt einen gcov-Bericht.
- Block 07 (dirty): keine automatisierte Testsuite; kein vergleichbarer Coverage-Wert.
- Coverage zeigt Ausführung, nicht die Aussagekraft der Tests.

## Grenzen der Messung

- Cognitive Complexity wird nicht erhoben.
- Heuristische Verschachtelung kann bei Makros und Kontrollstrukturen ohne Klammern abweichen.
- Cppcheck-Meldungen hängen von Version, Konfiguration und Analyseumfang ab.
- Die Analyse ermittelt keinen aggregierten Qualitätsscore.
- Lesbarkeit, fachliche Korrektheit und Architekturqualität benötigen Reviews und Tests.
