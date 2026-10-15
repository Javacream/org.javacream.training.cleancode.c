# Global State to Context

**Code Smell:** Ein globaler Zähler erschwert die unabhängige Nutzung und das Testen.

**Refactoring:** Zustand explizit in einer Kontextstruktur übergeben.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Die API ändert sich; Aufrufer müssen migriert und auf Verhalten geprüft werden.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
