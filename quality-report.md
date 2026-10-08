# Qualitätsanalyse – Clean-Code-Kurs

Erstellt: 2026-10-08T17:05:36+00:00

## Vergleich der Blöcke

| Block | Variante | C-Dateien | Funktionen | Summe NLOC (Funktionen) | Max. CCN | Max. Parameter | Cppcheck-Meldungen |
|---|---|---:|---:|---:|---:|---:|---:|
| 01 | clean | 1 | 2 | 16 | 2 | 2 | 0 |
| 01 | dirty | 1 | 1 | 11 | 2 | 0 | 1 |
| 02 | clean | 1 | 2 | 20 | 5 | 4 | 0 |
| 02 | dirty | 1 | 2 | 23 | 6 | 4 | 0 |
| 03 | clean | 1 | 1 | 12 | 4 | 0 | 1 |
| 03 | dirty | 1 | 1 | 10 | 4 | 0 | 3 |
| 04 | clean | 1 | 5 | 24 | 2 | 2 | 0 |
| 04 | dirty | 1 | 2 | 16 | 5 | 6 | 0 |
| 05 | clean | 1 | 2 | 15 | 8 | 4 | 0 |
| 05 | dirty | 1 | 2 | 20 | 8 | 4 | 0 |
| 06 | clean | 1 | 4 | 31 | 8 | 4 | 0 |
| 06 | dirty | 1 | 3 | 29 | 11 | 4 | 0 |
| 07 | clean | 3 | 4 | 29 | 4 | 3 | 0 |
| 07 | dirty | 1 | 2 | 11 | 1 | 1 | 0 |
| 08 | clean | 3 | 7 | 49 | 4 | 5 | 0 |
| 08 | dirty | 3 | 4 | 41 | 7 | 5 | 0 |

**Interpretation:** NLOC zählt nichtleere Codezeilen innerhalb erkannter Funktionen, CCN ist die zyklomatische Komplexität. Die Maximalwerte gelten pro Funktion; die Funktionsanzahl kann sich zwischen Varianten unterscheiden. Weniger ist nicht automatisch besser. Cppcheck-Meldungen sind Prüfhinweise und müssen fachlich bewertet werden.

## Auffällige Funktionen

| Block | Variante | Funktion | Datei | NLOC | CCN | Parameter |
|---|---|---|---|---:|---:|---:|
| 06 | dirty | `risk_score` | `main.c` | 17 | 11 | 4 |
| 05 | dirty | `shipping_cost` | `main.c` | 15 | 8 | 4 |
| 06 | clean | `incident_score` | `main.c` | 13 | 8 | 3 |
| 05 | clean | `shipping_cost` | `main.c` | 10 | 8 | 4 |
| 08 | dirty | `calculate_order_total` | `logic.c` | 13 | 7 | 5 |
| 02 | dirty | `process` | `main.c` | 17 | 6 | 4 |
| 02 | clean | `process` | `main.c` | 14 | 5 | 4 |
| 04 | dirty | `process_order` | `main.c` | 11 | 5 | 6 |
| 03 | clean | `main` | `main.c` | 12 | 4 | 0 |
| 03 | dirty | `main` | `main.c` | 10 | 4 | 0 |
| 08 | clean | `calculate_order_total` | `logic.c` | 9 | 4 | 5 |
| 06 | dirty | `category` | `main.c` | 7 | 4 | 1 |
| 06 | clean | `category` | `main.c` | 7 | 4 | 1 |
| 06 | clean | `risk_score` | `main.c` | 6 | 4 | 4 |
| 07 | clean | `calculate_gross_price` | `logic.c` | 5 | 4 | 2 |
| 08 | dirty | `main` | `test.c` | 14 | 2 | 0 |
| 08 | clean | `main` | `test.c` | 14 | 2 | 0 |
| 07 | clean | `main` | `test.c` | 13 | 2 | 0 |
| 01 | dirty | `main` | `main.c` | 11 | 2 | 0 |
| 08 | dirty | `expect` | `test.c` | 9 | 2 | 3 |

## Cppcheck-Befunde

### 01 - Grundlagen von Clean Code und Softwarequalit├ñt – dirty
- **style / knownConditionTrueFalse** – `main.c:8`: Condition 'r>300' is always true

### 03 - Namen, Datentypen und Ausdruckskraft – clean
- **style / knownConditionTrueFalse** – `main.c:10`: The comparison 'status == SHIPMENT_SENT' is always true because 'status' and 'SHIPMENT_SENT' represent the same value.

### 03 - Namen, Datentypen und Ausdruckskraft – dirty
- **style / knownConditionTrueFalse** – `main.c:8`: The comparison 's == 2' is always true.
- **style / knownConditionTrueFalse** – `main.c:8`: The comparison 'x == 1' is always true.
- **style / knownConditionTrueFalse** – `main.c:8`: The comparison 'y == 0' is always true.


## Grenzen der Messung

- Der Bericht misst ausgewählte strukturelle Eigenschaften, nicht Lesbarkeit, fachliche Korrektheit oder Architekturqualität.
- Die Anzahl der Cppcheck-Meldungen hängt von Version, Konfiguration und Analyseumfang ab.
- Es wird bewusst kein aggregierter Qualitätsscore berechnet.
- Tests, Reviews und Architekturentscheidungen ergänzen die Analyse.
