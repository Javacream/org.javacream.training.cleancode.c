# Replace Magic Number with Named Constant

**Code Smell:** Ein nicht erklärter Zahlenwert ist mehrfach im Code verstreut.

**Refactoring:** Den Wert benennen und zentral definieren.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
