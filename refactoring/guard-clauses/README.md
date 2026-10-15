# Replace Nested Conditional with Guard Clauses

**Code Smell:** Der Normalfall ist tief verschachtelt.

**Refactoring:** Ungültige Eingaben früh zurückweisen und den Normalfall freilegen.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
