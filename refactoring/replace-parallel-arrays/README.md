# Replace Parallel Arrays with Array of Structs

**Code Smell:** Zusammengehörige Daten sind nur über Array-Indizes verbunden.

**Refactoring:** Daten je Datensatz in einer struct zusammenführen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
