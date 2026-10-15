# Replace Conditional with Dispatch Table

**Code Smell:** Eine Typauswahl enthält mehrere austauschbare Berechnungen.

**Refactoring:** Funktionen durch eine Tabelle von Funktionszeigern auswählen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Eine Dispatch-Tabelle ist nicht automatisch besser als ein kurzer switch.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
