# Fachlicher Verhaltensvertrag – Versandkosten

Alle Stufen verwenden dieselben Regeln und liefern **Euro-Cent als `int`** zurück.

- Versandarten: `STANDARD`, `EXPRESS`, `PICKUP`.
- Abholung: 0 Cent; Standard Inland: 500 Cent; Standard Ausland: 2000 Cent.
- Express Inland: 1500 Cent; Express Ausland: 3500 Cent.
- Ab einem Warenwert von **10000 Cent** (einschließlich) werden bei STANDARD und EXPRESS **500 Cent** Versandrabatt gewährt; Versandkosten fallen nie unter 0.
- Gesperrte Aufträge und Aufträge mit Warenwert kleiner 0 werden mit `-1` abgewiesen.
- Eine unbekannte Versandart ist ebenfalls ungültig (`-1`).
- Keine Rundung oder Fließkommazahlen; Eingaben und Ergebnisse bleiben im demonstrierten Wertebereich von `int`.

Die Tests prüfen die Grenzwerte 9999/10000 Cent, alle Versandarten und Ziele sowie die Fehlerfälle. Ein Refactoring darf diese Regeln **nicht** ändern.
