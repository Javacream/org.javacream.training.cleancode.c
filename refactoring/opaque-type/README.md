# Expose Implementation to Opaque Type

**Code Smell:** Die öffentliche Struktur legt interne Repräsentation offen.

**Refactoring:** Im Header nur den unvollständigen Typ deklarieren.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Opaque Types können die Speicherverwaltung und API verändern; Tests müssen die Migration begleiten.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
