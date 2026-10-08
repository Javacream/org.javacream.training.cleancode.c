# ADR-0003: Zentrale PostgreSQL-Persistenz

**Status:** Accepted
**Ersetzt:** ADR-0002 (dateibasierte Persistenz)

## Kontext
Neue Anforderungen verlangen parallele Nutzung, konsistente Änderungen und atomare Speicherung zusammengehöriger Daten. Die bisherige Textdatei bietet dafür keine eingebauten Transaktionen oder Sperrmechanismen.

## Entscheidung
Eine zentrale PostgreSQL-Instanz übernimmt die Persistenz. Die Anwendung bleibt in C90 und verwendet die C-Bibliothek `libpq`. Die Datenbank läuft außerhalb der Entwicklungscontainer.

## Alternativen
- **Textdatei mit eigenen Sperren und Journal:** möglich, aber hohe Eigenkomplexität und Fehleranfälligkeit.
- **SQLite:** unterstützt ACID-Transaktionen, ist jedoch für eine zentrale Mehrbenutzeranwendung mit parallelen Schreibzugriffen weniger passend.
- **PostgreSQL:** Transaktionen, konkurrierende Verbindungen, zentrale Verwaltung und Open-Source-Lizenz.

## Konsequenzen
Zusätzlicher Serverbetrieb, Netzwerkabhängigkeit, Benutzerverwaltung und Fehlerfälle bei Verbindungsabbrüchen; dafür transaktionale und zentral verwaltete Speicherung. Die frühere Entscheidung war unter den alten Anforderungen angemessen; sie wird nicht nachträglich als grundsätzlich falsch bewertet.
