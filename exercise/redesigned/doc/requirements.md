# Neue Anforderungen (Phase 2)

Mehrere Sachbearbeiter müssen gleichzeitig auf Aufträge zugreifen können. Das Speichern eines Auftrags und seiner Positionen soll atomar erfolgen: vollständig oder gar nicht. Gleichzeitige Änderungen dürfen keine inkonsistenten Bestände erzeugen. Bei Fehlern müssen Änderungen zurückgerollt werden.

Die fachlichen Regeln für Versandkosten und Gesamtbeträge bleiben unverändert. Die Datenbank wird als zentrale PostgreSQL-Instanz **außerhalb** des Devcontainers bereitgestellt.
