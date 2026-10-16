# Replace Error Sentinel with Status and Output

**Code Smell:** Ein negativer Rückgabewert wird als Fehler interpretiert, obwohl negative Werte gültig sein können.

**Refactoring:** Erfolg und Ergebnis über getrennte Kanäle zurückgeben.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Bei der Migration ist der öffentliche API-Vertrag bewusst anzupassen; diese Änderung ist nicht allein ein verhaltensneutrales Refactoring.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c90 -Wall -Wextra -pedantic-errors -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.

## Verhaltenstest

Die gemeinsame Datei `test.c` liegt in diesem Verzeichnis und wird **unverändert** für `before` und `after` verwendet. Die jeweiligen `test_adapter.h`-Dateien passen nur die unterschiedlichen C-Schnittstellen an. In beiden Varianten `make test` ausführen. Die Tests prüfen fachliche Ergebnisse und ausgewählte Randfälle; sie beweisen keine vollständige Verhaltensäquivalenz.


## Lernziel und Refactoring-Vertrag

- **Ausgangsproblem:** Fehlerwert kollidiert mit gültigem Ergebnis.
- **Transformation:** Status und Ausgabewert trennen.
- **Erwartung:** Die gemeinsame `test.c` muss unter `before` und `after` dieselben fachlichen Ergebnisse bestätigen. Eine geänderte API kann darüber hinaus eigene Vertragstests benötigen.
- **Reflexion:** Gemeinsamer Adapter kann neue API-Semantik verdecken.

## Übungsablauf

1. `before` lesen, Problem und beobachtbares Verhalten notieren.
2. `make test` in `before` ausführen.
3. Transformation schrittweise in einer eigenen Arbeitskopie vornehmen.
4. `make test` in `after` ausführen; sofern vorhanden auch `make contract-test`.
5. Ergebnis mit Blick auf Lesbarkeit, Schnittstellen und Randfälle diskutieren.

**Erfolgskriterium:** Kompilierung im C90-Modus, unveränderte gemeinsame Verhaltenstests und eine nachvollziehbare Begründung für die strukturelle Verbesserung.
