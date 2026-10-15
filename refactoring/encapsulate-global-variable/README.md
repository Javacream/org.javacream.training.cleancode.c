# Encapsulate Variable in Module

**Code Smell:** Ein globaler Kontostand kann überall direkt verändert werden.

**Refactoring:** Daten hinter einer Modulschnittstelle verbergen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Der Zustand bleibt hier absichtlich ein einzelnes globales Konto innerhalb des Moduls.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
