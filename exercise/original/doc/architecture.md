# Ausgangsarchitektur

Die C90-Konsolenanwendung verwendet eine Textdatei als Datenspeicher. `src/main.c` enthält bewusst sowohl Geschäftsregeln als auch Dateioperationen, globale Daten, Eingabeprüfung und Darstellung. Diese Kopplung ist Bestandteil der Refactoring-Aufgabe und keine empfohlene Zielarchitektur.

Entscheidungen: [ADR-0001](adr-0001-use-c.md) und [ADR-0002](adr-0002-file-persistence.md). Die ursprünglichen Anforderungen verlangen weder konkurrierende Schreibzugriffe noch atomare Änderungen über mehrere Datensätze.
