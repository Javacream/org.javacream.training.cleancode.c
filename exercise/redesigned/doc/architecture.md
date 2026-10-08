# Zielarchitektur

Fachlogik: `order.c/.h`; Persistenz: `postgres_store.c/.h` mit PostgreSQL-`libpq`; Einstieg: `main.c`. Verbindungen werden über `PG_CONNINFO` konfiguriert; Zugangsdaten nicht ins Repository schreiben.

`postgres_save_order` schreibt den Auftragskopf und seine Positionen in einer expliziten `BEGIN`/`COMMIT`-Transaktion. Bei Fehlern wird `ROLLBACK` ausgeführt. `postgres_find_order` liest einen Auftrag; `postgres_cancel_order` storniert einen offenen Auftrag. Das Schema erzwingt Primär- und Fremdschlüssel sowie grundlegende Wertebereiche.

Die Datenbank liegt zentral **außerhalb** des Devcontainers. Ein eigenes Schema/eine eigene Datenbank pro Teilnehmer verhindert gegenseitige Testbeeinflussung.

**Grenzen:** Die Implementierung ist ein Architektur- und Transaktionsbeispiel, noch keine vollständige fachliche Portierung. Es gibt keine Listenfunktion, keinen Import aus `orders.txt`, keine vollständige Fehlerdiagnostik und noch keine reproduzierbaren Tests mit zwei konkurrierenden Verbindungen. Der Auftragswarenwert wird nicht aus den Positionen abgeleitet oder mit ihnen abgeglichen. Die `ON CONFLICT`-Aktualisierung besitzt keine Versionierung gegen verlorene Updates.

Siehe [ADR-0003](adr-0003-postgresql-persistence.md).
