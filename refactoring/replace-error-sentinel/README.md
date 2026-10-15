# Replace Error Sentinel with Status and Output

**Code Smell:** Ein negativer Rückgabewert wird als Fehler interpretiert, obwohl negative Werte gültig sein können.

**Refactoring:** Erfolg und Ergebnis über getrennte Kanäle zurückgeben.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Bei der Migration ist der öffentliche API-Vertrag bewusst anzupassen; diese Änderung ist nicht allein ein verhaltensneutrales Refactoring.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
