# PostgreSQL: Start und Integrationstest

Die PostgreSQL-Datenbank für das Beispiel `exercise/redesigned` wird mit Docker Compose gestartet. Alle folgenden Befehle werden im Verzeichnis `exercise/redesigned` ausgeführt.

## Datenbank starten

```bash
docker compose up -d
```

Beim ersten Start erzeugt PostgreSQL die Datenbank `orders` und führt `doc/schema.sql` aus. Die Daten bleiben im Docker-Volume `postgres_data` erhalten.

## Verbindung konfigurieren

Die C-Anwendung verwendet die Umgebungsvariable `PG_CONNINFO` für die Verbindung:

```bash
export PG_CONNINFO="host=localhost port=5432 dbname=orders user=orders password=orders"
```

Der Datenbankport ist auf `127.0.0.1:5432` des Docker-Hosts gebunden. Für die Ausführung innerhalb eines separaten Devcontainers muss die Hostadresse gegebenenfalls angepasst werden.

## Anwendung und Tests ausführen

```bash
make
make test
make integration-test
make run
```

`make test` führt die fachlichen Selbsttests ohne Datenbankzugriff aus. `make integration-test` prüft die PostgreSQL-Persistenz einschließlich Transaktions-Rollback. `make run` startet die Beispielanwendung.

Für die Übersetzung werden ein C-Compiler sowie die PostgreSQL-Clientbibliothek `libpq` und `pg_config` benötigt.

**Achtung:** Der Integrationstest verwendet die feste Auftrags-ID `900001` und verändert Datensätze. Daher ausschließlich eine isolierte Schulungsdatenbank verwenden.

## Datenbank stoppen

```bash
docker compose down
```

Die gespeicherten Daten bleiben erhalten. Soll die Datenbank einschließlich des Volumes zurückgesetzt werden:

```bash
docker compose down -v
```

Beim nächsten Start wird `doc/schema.sql` erneut ausgeführt.

## Zugangsdaten

Datenbank, Benutzer und Passwort heißen jeweils `orders`. Diese Zugangsdaten dienen nur der lokalen Schulungsumgebung und sind nicht für den Produktivbetrieb geeignet.
