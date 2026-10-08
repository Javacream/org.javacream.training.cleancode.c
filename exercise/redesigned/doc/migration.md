# Vorbereitung und Tests

1. Zentrale PostgreSQL-Instanz außerhalb des Devcontainers durch den Trainer bereitstellen.
2. Pro Teilnehmer eine isolierte Übungsdatenbank bzw. ein Schema einrichten.
3. `schema.sql` mit `psql` ausführen.
4. `libpq`-Entwicklungsbibliothek und `pg_config` im Devcontainer bereitstellen.
5. `PG_CONNINFO` als Umgebungsvariable konfigurieren (z. B. `host=... dbname=... user=...`), keine Passwörter einchecken.
6. `make`, `make test` und **nur in einer isolierten Übungsdatenbank** `make integration-test` ausführen.

Der Integrationstest schreibt Auftrag `900001`, prüft das Lesen, löst einen doppelten Positionsschlüssel aus, kontrolliert das Rollback des Auftragskopfes und storniert den Auftrag. Er verändert echte Daten in der angegebenen Datenbank. Er ist nicht für produktive Datenbanken geeignet.

`make clean` entfernt nur das Programm. Eine Migration vorhandener Textdateien ist noch nicht implementiert; sie erfordert Import und Validierung. Tests mit gleichzeitig schreibenden Clients sind ebenfalls noch offen.
