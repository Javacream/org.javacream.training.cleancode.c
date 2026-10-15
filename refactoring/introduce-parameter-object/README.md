# Introduce Parameter Object

**Code Smell:** Zusammengehörige Werte werden als lange Parameterliste übergeben.

**Refactoring:** Fachlich zusammengehörige Parameter in structs gruppieren.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
