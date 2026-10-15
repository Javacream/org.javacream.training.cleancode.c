# Make Ownership Explicit

**Code Smell:** Eine Funktion gibt allokierten Speicher zurück, ohne die Freigabeverantwortung zu verdeutlichen.

**Refactoring:** Ownership im API-Namen und Vertrag dokumentieren.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
