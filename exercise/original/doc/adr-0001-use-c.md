# ADR-0001: ANSI C90 als Implementierungssprache

**Status:** Accepted

## Kontext
Die Schulungsanwendung soll Funktionen, Datenstrukturen, Fehlerbehandlung, Modulgrenzen und Refactoring ohne zusätzliche Sprachkonzepte sichtbar machen.

## Entscheidung
Wir implementieren in ANSI C90.

## Alternativen
- **Java:** Für die gewählte Umsetzung werden objektorientierte Grundkenntnisse und eine JVM-Laufzeitumgebung vorausgesetzt. Dieser zusätzliche Lern- und Laufzeitaufwand ist hier nicht gewünscht.
- **Python:** Eine Interpreter-Laufzeitumgebung und die dazugehörige Ausführungsumgebung sind erforderlich; die Übung soll stattdessen C-Funktionen und explizite Speicher- und Ressourcenverwaltung zeigen.

## Konsequenzen
Kleine, direkt kompilierbare Beispiele; dafür explizite Speicher- und Fehlerbehandlung. Java und Python sind nicht generell ungeeignet, sondern passen weniger gut zu diesen Schulungszielen.
