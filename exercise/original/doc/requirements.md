# Fachliche Anforderungen

Eine kleine Auftragsverwaltung verwaltet Aufträge mit Auftragsnummer, Kundennummer, Warenwert in Cent, Gewicht in Gramm, Versandart und Status. Die Anwendung kann Aufträge anlegen, suchen und stornieren und berechnet Versandkosten und Gesamtbetrag.

Versandkosten: Standard 500 Cent, Express 1200 Cent; bei Gewicht über 5000 g zusätzlich 300 Cent; ab Warenwert 10000 Cent entfallen Standard-Versandkosten (Gewichtszuschlag bleibt). Stornierte Aufträge bleiben lesbar. Keine Mehrbenutzer- oder Transaktionsanforderungen in dieser Version.

Die Datei `orders.txt` ist zeilenorientiert und kann manuell gelesen und bearbeitet werden. Format: `id;customer;subtotal_cents;weight_g;shipping;status`. Auftragsnummern müssen eindeutig sein; höchstens 100 Aufträge werden geladen. Demo-Daten werden durch das Programm erzeugt, falls keine Datei existiert.
