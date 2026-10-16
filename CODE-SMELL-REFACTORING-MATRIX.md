# Code Smells und geeignete Refactorings

| Code Smell / Beobachtung | Geeignete Technik | Einschränkung |
|---|---|---|
| Lange Funktion | Extract Function | Nur bei sinnvoller Abstraktion |
| Magische Zahl | Replace Magic Number | Fachlichen Gültigkeitsbereich beachten |
| Tiefe Verschachtelung | Guard Clauses | Fehlerpfade nicht ändern |
| Wiederkehrende Parametergruppe | Introduce Parameter Object | Fachliche Kohärenz nötig |
| Parsing und Berechnung vermischt | Split Phase | Fehlerverhalten prüfen |
| Parallele Arrays | Replace Parallel Arrays | Indexzuordnung erhalten |
| Global veränderlicher Zustand | Encapsulate Global Variable | Noch kein unabhängiger Kontext |
| Impliziter globaler Zustand | Global State to Context | Lebenszyklus klären |
| Große Auswahl gleichartiger Aktionen | Replace Conditional with Dispatch | `switch` kann einfacher sein |
| Fehler-Sentinel | Replace Error Sentinel | API-Vertrag ändert sich |
| Wiederholte Ressourcenfreigabe | Extract Resource Cleanup | Alle Fehlerpfade testen |
| Unklare Ownership | Make Ownership Explicit | Vertrag dokumentieren |
| Öffentliche Implementierungsdetails | Opaque Type | Allokation / API-Kompatibilität prüfen |

## Leitfragen

1. Welches beobachtbare Problem soll gelöst werden?
2. Welche Änderung ist strukturell, welche verändert den fachlichen Vertrag?
3. Welcher Test belegt das alte Verhalten, welcher einen neuen API-Vertrag?
4. Verbessert die Transformation die Verständlichkeit tatsächlich?
