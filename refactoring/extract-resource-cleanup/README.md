# Extract Resource Cleanup

**Code Smell:** Mehrere Fehlerpfade duplizieren Ressourcenfreigaben.

**Refactoring:** Einen gemeinsamen Cleanup-Pfad verwenden.

**Vorher:** [`before/`](before/) – Ausgangszustand.

**Nachher:** [`after/`](after/) – überarbeiteter Zustand.

**Diskussion:** Ein gezieltes goto cleanup ist in C häufig besser als duplizierte Freigabewege.

**Prüfen:** Im jeweiligen Verzeichnis `gcc -std=c11 -Wall -Wextra -Wpedantic *.c -o example && ./example` ausführen.
