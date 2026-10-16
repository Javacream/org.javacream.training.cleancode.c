# Replace Conditional with Dispatch Table

**Code Smell:** Eine Typauswahl enthält mehrere austauschbare Berechnungen.

**Refactoring:** Funktionen durch eine Tabelle von Funktionszeigern auswählen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Eine Dispatch-Tabelle ist nicht automatisch besser als ein kurzer switch.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c90 -Wall -Wextra -pedantic-errors -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.

## Verhaltenstest

Die gemeinsame Datei `test.c` liegt in diesem Verzeichnis und wird **unverändert** für `before` und `after` verwendet. Die jeweiligen `test_adapter.h`-Dateien passen nur die unterschiedlichen C-Schnittstellen an. In beiden Varianten `make test` ausführen. Die Tests prüfen fachliche Ergebnisse und ausgewählte Randfälle; sie beweisen keine vollständige Verhaltensäquivalenz.


## Lernziel und Refactoring-Vertrag

- **Ausgangsproblem:** Wiederkehrende Fallunterscheidung.
- **Transformation:** Funktionszeiger-Tabelle.
- **Erwartung:** Die gemeinsame `test.c` muss unter `before` und `after` dieselben fachlichen Ergebnisse bestätigen. Eine geänderte API kann darüber hinaus eigene Vertragstests benötigen.
- **Reflexion:** Ist switch bei wenigen Fällen nicht verständlicher?

## Übungsablauf

1. `before` lesen, Problem und beobachtbares Verhalten notieren.
2. `make test` in `before` ausführen.
3. Transformation schrittweise in einer eigenen Arbeitskopie vornehmen.
4. `make test` in `after` ausführen; sofern vorhanden auch `make contract-test`.
5. Ergebnis mit Blick auf Lesbarkeit, Schnittstellen und Randfälle diskutieren.

**Erfolgskriterium:** Kompilierung im C90-Modus, unveränderte gemeinsame Verhaltenstests und eine nachvollziehbare Begründung für die strukturelle Verbesserung.
