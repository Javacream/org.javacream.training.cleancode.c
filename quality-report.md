# Qualitätsanalyse – Clean-Code-Kurs

Erstellt: 2026-10-08T18:08:09+00:00

## Vergleich der Blöcke

| Block | Variante | C-Dateien | Funktionen | Summe NLOC (Funktionen) | Max. CCN | Verschachtelung (heur.) | Max. Parameter | Cppcheck-Meldungen |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| 01 | clean | 1 | 2 | 16 | 2 | 1 | 2 | 0 |
| 01 | dirty | 1 | 1 | 11 | 2 | 1 | 0 | 1 |
| 02 | clean | 1 | 2 | 20 | 5 | 0 | 4 | 0 |
| 02 | dirty | 1 | 2 | 23 | 6 | 0 | 4 | 0 |
| 03 | clean | 1 | 1 | 26 | 16 | 1 | 1 | 1 |
| 03 | dirty | 1 | 1 | 16 | 16 | 1 | 1 | 1 |
| 04 | clean | 1 | 5 | 24 | 2 | 1 | 2 | 0 |
| 04 | dirty | 1 | 2 | 16 | 5 | 1 | 6 | 0 |
| 05 | clean | 1 | 2 | 15 | 8 | 1 | 4 | 0 |
| 05 | dirty | 1 | 2 | 20 | 8 | 3 | 4 | 0 |
| 06 | clean | 1 | 4 | 31 | 8 | 1 | 4 | 0 |
| 06 | dirty | 1 | 3 | 29 | 11 | 2 | 4 | 0 |
| 07 | clean | 3 | 4 | 33 | 4 | 1 | 3 | 0 |
| 07 | dirty | 1 | 2 | 11 | 1 | 0 | 1 | 0 |
| 08 | clean | 3 | 7 | 49 | 4 | 1 | 5 | 0 |
| 08 | dirty | 3 | 4 | 41 | 7 | 2 | 5 | 0 |

**Interpretation:** Die Verschachtelung ist eine vereinfachte, nicht normierte Klammer-Heuristik. NLOC zählt nichtleere Codezeilen innerhalb erkannter Funktionen, CCN ist die zyklomatische Komplexität. Die Maximalwerte gelten pro Funktion; die Funktionsanzahl kann sich zwischen Varianten unterscheiden. Weniger ist nicht automatisch besser. Cppcheck-Meldungen sind Prüfhinweise und müssen fachlich bewertet werden.

## Funktionen mit der höchsten zyklomatischen Komplexität

| Block | Variante | Funktion | Datei | NLOC | CCN | Parameter |
|---|---|---|---|---:|---:|---:|
| 03 | clean | `main` | `main.c` | 26 | 16 | 1 |
| 03 | dirty | `main` | `main.c` | 16 | 16 | 1 |
| 06 | dirty | `risk_score` | `main.c` | 17 | 11 | 4 |
| 05 | dirty | `shipping_cost` | `main.c` | 15 | 8 | 4 |
| 06 | clean | `incident_score` | `main.c` | 13 | 8 | 3 |
| 05 | clean | `shipping_cost` | `main.c` | 10 | 8 | 4 |
| 08 | dirty | `calculate_order_total` | `logic.c` | 13 | 7 | 5 |
| 02 | dirty | `process` | `main.c` | 17 | 6 | 4 |
| 02 | clean | `process` | `main.c` | 14 | 5 | 4 |
| 04 | dirty | `process_order` | `main.c` | 11 | 5 | 6 |

## Cppcheck-Befunde

### 01 - Grundlagen von Clean Code und Softwarequalität – dirty
- **style / knownConditionTrueFalse** – `main.c:8`: Condition 'r>300' is always true

### 03 - Namen, Datentypen und Ausdruckskraft – clean
- **style / constParameter** – `main.c:4`: Parameter 'argv' can be declared as const array

### 03 - Namen, Datentypen und Ausdruckskraft – dirty
- **style / constParameter** – `main.c:2`: Parameter 'argv' can be declared as const array


## Testqualität und Coverage

- Block 07 (clean): `make check` führt die Tests aus; `make coverage` erzeugt einen gcov-Bericht für `logic.c`.
- Block 07 (dirty): keine automatisierte Testsuite. Ein numerischer Coverage-Vergleich wäre deshalb irreführend.
- Coverage zeigt ausgeführte Zeilen/Zweige, aber nicht die Aussagekraft der Tests.

## Grenzen der Messung

- Der Bericht misst ausgewählte strukturelle Eigenschaften, nicht Lesbarkeit, fachliche Korrektheit oder Architekturqualität.
- Die Anzahl der Cppcheck-Meldungen hängt von Version, Konfiguration und Analyseumfang ab.
- Es wird bewusst kein aggregierter Qualitätsscore berechnet.
- Tests, Reviews und Architekturentscheidungen ergänzen die Analyse.
