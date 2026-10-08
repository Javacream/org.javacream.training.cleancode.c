# Abschlussübung: Auftragsverwaltung

Zwei Schritte: (1) Code Smells bereinigen, ohne Verhalten oder dateibasierte Persistenz zu verändern; (2) neue Anforderungen an Mehrbenutzerfähigkeit und atomare Änderungen bewerten und eine relationale Persistenz realisieren.

`original/` ist der Ausgangspunkt auf `training`. Musterlösungen `reworked/` und `redesigned/` liegen ausschließlich auf `training-solution`.

Build: `make -C exercise/original`; Test: `make -C exercise/original test`. Die Beispieldatei wird nur im Laufzeitverzeichnis erzeugt. Die Originalimplementierung ist absichtlich verbesserungswürdig. Vor Änderungen Tests ergänzen, anschließend Metriken vergleichen.
