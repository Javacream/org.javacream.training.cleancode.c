# Extract Function

**Code Smell:** Eine Funktion mischt Summierung und Steuerberechnung.

**Refactoring:** Einen zusammenhängenden Berechnungsschritt in eine statische Hilfsfunktion extrahieren.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Prüfen, ob die Struktur verständlicher ist und ob das beobachtbare Verhalten erhalten bleibt.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
