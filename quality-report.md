# Qualitätsanalyse – Clean-Code-Kurs

Erstellt: 2026-10-08T17:31:22+00:00

## Vergleich der Blöcke

| Block | Variante | C-Dateien | Funktionen | Summe NLOC (Funktionen) | Max. CCN | Max. Cognitive | Verschachtelung (heur.) | Max. Parameter | Cppcheck-Meldungen |
|---|---|---:|---:|---:|---:|---:|---:|
| 01 | clean | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 01 | dirty | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 1 |
| 02 | clean | 1 | 0 | 0 | 0 | n/a | 0 | 0 | 0 |
| 02 | dirty | 1 | 0 | 0 | 0 | n/a | 0 | 0 | 0 |
| 03 | clean | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 1 |
| 03 | dirty | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 1 |
| 04 | clean | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 04 | dirty | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 05 | clean | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 05 | dirty | 1 | 0 | 0 | 0 | n/a | 3 | 0 | 0 |
| 06 | clean | 1 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 06 | dirty | 1 | 0 | 0 | 0 | n/a | 2 | 0 | 0 |
| 07 | clean | 3 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 07 | dirty | 1 | 0 | 0 | 0 | n/a | 0 | 0 | 0 |
| 08 | clean | 3 | 0 | 0 | 0 | n/a | 1 | 0 | 0 |
| 08 | dirty | 3 | 0 | 0 | 0 | n/a | 2 | 0 | 0 |

**Interpretation:** Cognitive Complexity stammt aus der Lizard-Erweiterung; die Verschachtelung ist eine vereinfachte, nicht normierte Klammer-Heuristik. NLOC zählt nichtleere Codezeilen innerhalb erkannter Funktionen, CCN ist die zyklomatische Komplexität. Die Maximalwerte gelten pro Funktion; die Funktionsanzahl kann sich zwischen Varianten unterscheiden. Weniger ist nicht automatisch besser. Cppcheck-Meldungen sind Prüfhinweise und müssen fachlich bewertet werden.

## Auffällige Funktionen

| Block | Variante | Funktion | Datei | NLOC | CCN | Cognitive | Parameter |
|---|---|---|---|---:|---:|---:|---:|

## Cppcheck-Befunde

### 01 - Grundlagen von Clean Code und SoftwarequalitÔö£├▒t – dirty
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
