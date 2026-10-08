# ADR-0002: Dateibasierte Persistenz

**Status:** Accepted (für die Ausgangsanforderungen)

## Kontext
Die Auftragsverwaltung wird zunächst lokal und ohne konkurrierende Zugriffe genutzt. Daten sollen unkompliziert kontrolliert und korrigiert werden können.

## Entscheidung
Wir speichern Aufträge in einer zeilenorientierten Textdatei.

## Alternativen
- **Relationale Datenbank:** Bietet Transaktionen und Nebenläufigkeitskontrolle, erfordert jedoch zusätzliche Infrastruktur und Betriebskenntnisse; je nach Produkt oder Betriebsmodell können Kosten anfallen.
- **Eingebettete Datenbank:** Weniger Betriebsaufwand als ein Server, aber weiterhin zusätzliche Bibliothek und Datenformat.

## Gründe
Einfache Architektur; kein zusätzlicher Datenbankserver; keine Abhängigkeit von potenziell kostenpflichtigen Produkten; Daten lassen sich direkt mit einem Texteditor lesen und bearbeiten.

## Konsequenzen
Geringe Einstiegshürde. Bewusst akzeptiert werden fehlende integrierte Transaktionen, begrenzte Nebenläufigkeit und Risiken bei unterbrochenen Schreibvorgängen. Bei geänderten Anforderungen neu bewerten.
