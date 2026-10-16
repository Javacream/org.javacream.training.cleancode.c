# Replace Parallel Arrays with Array of Structs

**Code Smell:** Zusammengehörige Daten sind nur über Array-Indizes verbunden.

**Refactoring:** Daten je Datensatz in einer struct zusammenführen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c90 -Wall -Wextra -pedantic-errors -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.

## Verhaltenstest

Die gemeinsame Datei `test.c` liegt in diesem Verzeichnis und wird **unverändert** für `before` und `after` verwendet. Die jeweiligen `test_adapter.h`-Dateien passen nur die unterschiedlichen C-Schnittstellen an. In beiden Varianten `make test` ausführen. Die Tests prüfen fachliche Ergebnisse und ausgewählte Randfälle; sie beweisen keine vollständige Verhaltensäquivalenz.


## Lernziel und Refactoring-Vertrag

- **Ausgangsproblem:** Durch Indizes gekoppelte Arrays.
- **Transformation:** Array von Strukturen.
- **Erwartung:** Die gemeinsame `test.c` muss unter `before` und `after` dieselben fachlichen Ergebnisse bestätigen. Eine geänderte API kann darüber hinaus eigene Vertragstests benötigen.
- **Reflexion:** Was passiert beim Einfügen oder Sortieren?

## Übungsablauf

1. `before` lesen, Problem und beobachtbares Verhalten notieren.
2. `make test` in `before` ausführen.
3. Transformation schrittweise in einer eigenen Arbeitskopie vornehmen.
4. `make test` in `after` ausführen; sofern vorhanden auch `make contract-test`.
5. Ergebnis mit Blick auf Lesbarkeit, Schnittstellen und Randfälle diskutieren.

**Erfolgskriterium:** Kompilierung im C90-Modus, unveränderte gemeinsame Verhaltenstests und eine nachvollziehbare Begründung für die strukturelle Verbesserung.
