# Trainerleitfaden – Clean Code mit ANSI C90

**Stand:** 09.11.2026  
**Zielgruppe:** Entwicklerinnen und Entwickler mit C-Grundkenntnissen  
**Material:** [Kurs-README](../README.md), [Seminarblöcke](../blocks/), [Refactoring-Katalog](../refactoring/README.md), [Code-Smell-/Refactoring-Matrix](../CODE-SMELL-REFACTORING-MATRIX.md), [Qualitätsbericht](../quality-report.md)

## Einsatz und Zeitmodell

Dieser Leitfaden beschreibt den **vollständigen sinnvollen Lernpfad**, nicht eine auf zwei Tage gekürzte Agenda. Alle Zeiten sind **Netto-Unterrichtszeit** einschließlich Demonstration, eigenständiger Arbeit, Tests, Besprechung und typischer Rückfragen, **ohne Pausen**. Die Zeitansätze gelten für eine Gruppe mit C-Grundkenntnissen und funktionierendem Devcontainer; größere Gruppen oder ungeübte C-Teilnehmende benötigen mehr Zeit.

- **mandatory:** Kernstoff, der für das Verständnis der nachfolgenden Einheiten erforderlich ist.
- **optional:** eigenständige Vertiefung; bei Zeitknappheit weglassen, ohne den Pflichtpfad zu unterbrechen.
- **Arbeitsprinzip:** Ausgangscode untersuchen → erwartetes Verhalten festhalten → Tests bzw. Ausgabe prüfen → Änderung durchführen → erneut prüfen → mit Referenzversion vergleichen.
- **Didaktische Regel:** `dirty/` und `before/` zuerst zeigen; `clean/` und `after/` erst nach der Bearbeitung öffnen. Bei den Refactoring-Beispielen dienen die unveränderten gemeinsamen Tests als Verhaltensnachweis, nicht als Beweis vollständiger Äquivalenz.
- **Hinweis zur Zeitplanung:** Die vollständige Durchführung aller optionalen Übungen ist ausdrücklich **nicht** als Zweitagesseminar gedacht.

## Zeitübersicht

| Einheit | Thema | Priorität | Dauer |
|---|---|---|---:|
| 00 | Einführung und Arbeitsumgebung | mandatory | 45 min |
| 01 | Clean-Code-Grundlagen und Prinzipien | mandatory | 105 min |
| 02 | Code Smells erkennen und priorisieren | mandatory | 90 min |
| 03 | Namen, Datentypen und Ausdruckskraft | mandatory | 90 min |
| 04 | Funktionen und Verantwortlichkeiten | mandatory | 120 min |
| 05 | Kontrollfluss und Guard Clauses | mandatory | 105 min |
| 06 | Metriken und statische Codeanalyse | mandatory | 120 min |
| 07 | Testbarkeit und Clean Tests | mandatory | 135 min |
| 08 | Refactoring als schrittweiser Prozess | mandatory | 150 min |
| 09 | Extract Function – isolierte Übung | optional | 45 min |
| 10 | Replace Magic Number – isolierte Übung | optional | 30 min |
| 11 | Guard Clauses – isolierte Übung | optional | 45 min |
| 12 | Introduce Parameter Object | optional | 60 min |
| 13 | Split Phase | optional | 60 min |
| 14 | Replace Parallel Arrays | optional | 60 min |
| 15 | Replace Conditional with Dispatch Table | optional | 75 min |
| 16 | Encapsulate Global Variable | optional | 60 min |
| 17 | Global State to Context | optional | 75 min |
| 18 | Replace Error Sentinel | optional | 75 min |
| 19 | Extract Resource Cleanup | optional | 75 min |
| 20 | Opaque Type | optional | 75 min |
| 21 | Make Ownership Explicit | optional | 75 min |
| 22 | Gesamtreview und Transfer | optional | 45 min |

**Gesamt mandatory:** 960 min = **16 h Netto-Unterricht**.  
**Gesamt optional:** 855 min = **14 h 15 min Netto-Unterricht**.  
**Vollständiges Programm:** **30 h 15 min Netto-Unterricht**, zuzüglich Pausen. Bei etwa 6 h Netto-Unterricht pro Seminartag entspricht das gut **fünf Seminartagen**. Die optionalen Einheiten 09–21 sind alternative Vertiefungen, keine zwingend lineare Fortsetzung.

---

## Einheit 00 – Einführung und Arbeitsumgebung
**Priorität:** mandatory · **Dauer:** 45 min

**Ziel:** Die Teilnehmenden verstehen Aufbau, Arbeitsweise und Verhaltensvertrag der Übungen.

**Ablauf:** 10 min Zielsetzung und Unterschied Clean Code/Fehlerfreiheit; 15 min Devcontainer, VS Code und Verzeichnisstruktur; 10 min Kompilieren, Starten und Testen; 10 min Fragen und Vorbereitung.

**Präsentation/Demo:** [Projekt-README](../README.md), `.devcontainer/`, `.vscode/tasks.json`, `blocks/01-grundlagen/dirty/`. Gemeinsam ein Beispiel mit `make` und `make test` ausführen. Den zentralen Testlauf `make test` nur demonstrieren, nicht 42 Verzeichnisse einzeln besprechen.

**Trainerhinweis:** `-std=c90` und `-pedantic-errors` einordnen; nicht voraussetzen, dass Run/Debug-Buttons und Make-Targets identisch funktionieren.

## Einheit 01 – Clean-Code-Grundlagen, Prinzipien und Dokumentation
**Priorität:** mandatory · **Dauer:** 105 min

**Ziel:** Lesbarkeit, Wartbarkeit, Testbarkeit, KISS/DRY/YAGNI, technische Schulden, selbstdokumentierenden Code und ADRs unterscheiden.

**Ablauf:** 30 min Einführung und Prinzipien; 15 min Live-Code-Review; 30 min Gruppenübung; 20 min Vergleich und Diskussion; 10 min ADR-/Technical-Debt-Transfer.

**Übung:** [Block 01](../blocks/01-grundlagen/README.md) mit `dirty/main.c`, `dirty/doc.md` und `clean/main.c`. Drei Verständnishürden markieren, Aussagen der Dokumentation auf notwendige und entbehrliche Inhalte prüfen, KISS/DRY/YAGNI auf Verbesserungen anwenden.

**Trainerhinweis:** Ein ADR dokumentiert Gründe einer Entscheidung und ist kein Ersatz für lesbaren Code. Nicht jede Duplikation rechtfertigt eine Abstraktion.

## Einheit 02 – Code Smells erkennen und priorisieren
**Priorität:** mandatory · **Dauer:** 90 min

**Ziel:** Code Smells von Bugs unterscheiden und Befunde nach Wirkung, Risiko und Aufwand priorisieren.

**Ablauf:** 20 min Smell-Kategorien und Matrix; 15 min moderiertes Beispiel; 30 min Zweiergruppenanalyse; 15 min Priorisierung; 10 min Review.

**Übung:** [Block 02](../blocks/02-code-smells/README.md), `dirty/main.c` und [Code-Smell-/Refactoring-Matrix](../CODE-SMELL-REFACTORING-MATRIX.md). Mindestens drei Fundstellen dokumentieren, zwei priorisieren, eine kleine Änderung begründen, Ergebnis mit `clean` vergleichen.

**Trainerhinweis:** Die umfangreiche Umstrukturierung bewusst zurückstellen: Sie gehört in Einheiten 04, 05 und 08.

## Einheit 03 – Namen, Datentypen und Ausdruckskraft
**Priorität:** mandatory · **Dauer:** 90 min

**Ziel:** Intention durch Namen, `enum`, `unsigned int` und sinnvolle C90-Darstellung boolescher Aussagen ausdrücken.

**Ablauf:** 20 min Theorie und C90-Grenzen; 15 min Code-Walkthrough; 35 min Umbenennen/Typisieren; 20 min Eingabevergleich und Diskussion.

**Übung:** [Block 03](../blocks/03-namen-datentypen/README.md), `dirty/main.c` → `clean/main.c`. Die vier dokumentierten Kommandozeilenkombinationen ausführen und Verhalten vergleichen.

**Trainerhinweis:** Keine Funktionszerlegung erzwingen. Eine unveränderte CCN ist hier erwartbar; Verständlichkeit ist das Lernziel.

## Einheit 04 – Funktionen und Verantwortlichkeiten
**Priorität:** mandatory · **Dauer:** 120 min

**Ziel:** Validierung, Berechnung und Ausgabe trennen, Funktionsgrenzen begründen, lange Parameterlisten hinterfragen.

**Ablauf:** 25 min Entwurfsprinzipien; 20 min Zerlegung am Ausgangscode planen; 50 min eigenständige Umsetzung; 15 min Test/Referenzvergleich; 10 min Diskussion.

**Übung:** [Block 04](../blocks/04-funktionen/README.md), `dirty/main.c` → `clean/main.c`. Die Option `print_details` ausdrücklich in beiden Zuständen prüfen.

**Präsentationsanker:** [Extract Function](../refactoring/extract-function/README.md) als **kurze Technikdemonstration** (5–10 min innerhalb der Einheit); die eigenständige Übung ist Einheit 09.

**Trainerhinweis:** Funktionszahl ist kein Qualitätsziel; fachliche Verantwortlichkeiten und Parameterübergabe sind wichtiger.

## Einheit 05 – Kontrollfluss, Guard Clauses und switch
**Priorität:** mandatory · **Dauer:** 105 min

**Ziel:** Fehlerpfade sichtbar machen und verschachtelte Entscheidungen strukturieren, ohne Rückgabewerte zu verändern.

**Ablauf:** 20 min Kontrollflussmuster; 20 min gemeinsame Pfadanalyse; 40 min Übung; 15 min Testfälle; 10 min Diskussion.

**Übung:** [Block 05](../blocks/05-kontrollfluss/README.md), `dirty/main.c` → `clean/main.c`. Abholung, Standard, Express, Inland/Ausland, gesperrte und ungültige Fälle berücksichtigen.

**Präsentationsanker:** [Guard Clauses](../refactoring/guard-clauses/README.md) kurz zeigen; vollständige eigenständige Übung in Einheit 11.

**Trainerhinweis:** Guard Clauses verändern nicht zwangsläufig die CCN. Priorität der Fehlerprüfungen und Fehlercodes beibehalten.

## Einheit 06 – Metriken und statische Codeanalyse
**Priorität:** mandatory · **Dauer:** 120 min

**Ziel:** NLOC, CCN, Parameteranzahl, heuristische Verschachtelung und Cppcheck-Befunde kritisch interpretieren.

**Ablauf:** 25 min Metrikgrundlagen; 20 min Tool-Demo; 35 min Berichtsanalyse in Gruppen; 25 min Code- und Variantenvergleich; 15 min Ergebnissicherung.

**Übung:** [Block 06](../blocks/06-metriken/README.md), `dirty/main.c`, `clean/main.c`, `clean/alternative.c`, `clean/test_comparison.c`; [Qualitätsbericht](../quality-report.md). Ausführen:
```sh
python3 analyze.py --output quality-report.md
python3 analyze.py --block 06 --output blocks/06-metriken/quality-report-block06.md
make -C blocks/06-metriken/clean compare
```
**Trainerhinweis:** Testcode und alternative Implementierung sind aus dem direkten Dirty/Clean-Metrikvergleich ausgeschlossen. Besonders Block 03 (gleiche CCN), Block 05 (geringere Verschachtelung bei gleicher CCN) und Block 07 (Testbarkeit nicht durch CCN erfasst) diskutieren. Die Heuristik ist keine normierte Metrik.

## Einheit 07 – Testbarkeit und Clean Tests
**Priorität:** mandatory · **Dauer:** 135 min

**Ziel:** Abhängigkeiten von globalem Zustand und I/O auflösen, fachlich begründete Tests ergänzen und Coverage einordnen.

**Ablauf:** 25 min Testbarkeit und Charakterisierung; 20 min Ausgangscode und Referenzstruktur; 55 min eigene Tests/Änderungen; 20 min Coverage-Demo; 15 min Review.

**Übung:** [Block 07](../blocks/07-testbarkeit/README.md), `dirty/main.c`, `clean/main.c`, `clean/logic.c`, `clean/test.c`. In `blocks/07-testbarkeit/clean/`: `make check` und `make coverage`. Mindestens einen fachlich begründeten weiteren Testfall ergänzen.

**Trainerhinweis:** Keine neuen Validierungsregeln als Refactoring einschmuggeln. Die Dirty-Variante hat bewusst keine eigene Testsuite; Coverage nicht numerisch vergleichen.

## Einheit 08 – Refactoring als schrittweiser Prozess
**Priorität:** mandatory · **Dauer:** 150 min

**Ziel:** Mehrere Refactoring-Techniken in kleinen, abgesicherten Schritten kombinieren.

**Ablauf:** 20 min Fowler-Ansatz und Verhaltensvertrag; 20 min Smells und Plan; 70 min Umsetzung mit Test nach jedem Schritt; 25 min Referenzvergleich; 15 min Reflexion.

**Übung:** [Block 08](../blocks/08-refactoring/README.md), `dirty/logic.c`, `dirty/test.c` und die Clean-Referenz. Erst `make check`, dann mindestens zwei getrennte Änderungen (z. B. Namen, Konstanten, Funktionszerlegung, Guard Clauses) mit erneutem Testlauf nach jedem Schritt.

**Trainerhinweis:** Das ist die zentrale Integrationsübung. Keine `after`-Lösung vorzeitig zeigen; mehrere fachlich gleichwertige Lösungen zulassen.

---

## Einheit 09 – Extract Function
**Priorität:** optional · **Dauer:** 45 min

**Übung:** [Extract Function](../refactoring/extract-function/README.md). Summierung und Steuerberechnung trennen; Namen, Eingaben und Rückgabe des extrahierten Schritts begründen. **Ablauf:** 10 min Analyse, 25 min Umsetzung und `make test`, 10 min Review. **Hinweis:** Ganzzahlarithmetik und Berechnungsreihenfolge erhalten.

## Einheit 10 – Replace Magic Number with Named Constant
**Priorität:** optional · **Dauer:** 30 min

**Übung:** [Replace Magic Number](../refactoring/replace-magic-number/README.md). Fachliche Zahl identifizieren, Gültigkeitsbereich einer Konstante wählen, unveränderte Ergebnisse testen. **Ablauf:** 5 min Problem, 15 min Umsetzung/Test, 10 min Diskussion. **Hinweis:** Nicht jede Zahl ist eine unveränderliche Fachkonstante.

## Einheit 11 – Replace Nested Conditional with Guard Clauses
**Priorität:** optional · **Dauer:** 45 min

**Übung:** [Guard Clauses](../refactoring/guard-clauses/README.md). Normal- und Fehlerpfade trennen, Rückgabewerte und Prüfpriorität erhalten. **Ablauf:** 10 min Analyse, 25 min Umsetzung/Test, 10 min Review.

## Einheit 12 – Introduce Parameter Object
**Priorität:** optional · **Dauer:** 60 min

**Übung:** [Introduce Parameter Object](../refactoring/introduce-parameter-object/README.md). Zusammengehörige Parameter in einer C-`struct` bündeln und Auswirkungen auf Aufrufer diskutieren. **Ablauf:** 15 min API-Analyse, 30 min Umsetzung/Test, 15 min Review.

## Einheit 13 – Split Phase
**Priorität:** optional · **Dauer:** 60 min

**Übung:** [Split Phase](../refactoring/split-phase/README.md). Parsing von Berechnung trennen; ungültige und zu große Eingaben beachten. **Ablauf:** 15 min Phasenentwurf, 30 min Umsetzung/Test, 15 min Diskussion.

## Einheit 14 – Replace Parallel Arrays with Array of Structs
**Priorität:** optional · **Dauer:** 60 min

**Übung:** [Replace Parallel Arrays](../refactoring/replace-parallel-arrays/README.md). Zusammengehörige Daten in `struct`-Elementen organisieren; Indexkopplung und Datenkonsistenz diskutieren. **Ablauf:** 15 min Analyse, 30 min Umsetzung/Test, 15 min Review.

## Einheit 15 – Replace Conditional with Dispatch Table
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Replace Conditional with Dispatch](../refactoring/replace-conditional-with-dispatch/README.md). Verzweigungen durch Funktionszeiger/Dispatch-Tabelle strukturieren. **Ablauf:** 20 min Konzept, 40 min Umsetzung/Test, 15 min Diskussion. **Hinweis:** Abstraktionsaufwand und Verständlichkeit gegen `switch` abwägen.

## Einheit 16 – Encapsulate Global Variable
**Priorität:** optional · **Dauer:** 60 min

**Übung:** [Encapsulate Global Variable](../refactoring/encapsulate-global-variable/README.md). Globale Variable über Modulgrenzen kapseln; Schnittstelle und verbleibende globale Kopplung beurteilen. **Ablauf:** 15 min Analyse, 30 min Umsetzung/Test, 15 min Review.

## Einheit 17 – Global State to Context
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Global State to Context](../refactoring/global-state-to-context/README.md). Zustand explizit übergeben, unabhängige Kontexte prüfen. **Ablauf:** 20 min API-/Zustandsanalyse, 40 min Umsetzung/Verhaltens- und Contract-Tests, 15 min Review. **Hinweis:** API-Migration und zusätzliche Instanzunabhängigkeit ausdrücklich von reinem Refactoring unterscheiden.

## Einheit 18 – Replace Error Sentinel with Status and Output
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Replace Error Sentinel](../refactoring/replace-error-sentinel/README.md). Fehlerstatus und Ergebniswert getrennt übermitteln. **Ablauf:** 20 min Fehlervertrag, 40 min Umsetzung/Verhaltens- und Contract-Tests, 15 min Diskussion. **Hinweis:** API-Vertrag kann sich ändern.

## Einheit 19 – Extract Resource Cleanup
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Extract Resource Cleanup](../refactoring/extract-resource-cleanup/README.md). Ressourcenpfade analysieren und einen gemeinsamen Cleanup-Pfad, gegebenenfalls mit `goto cleanup`, gestalten. **Ablauf:** 20 min Pfadanalyse, 40 min Umsetzung/Verhaltens- und Contract-Tests, 15 min Review. **Hinweis:** Test-Erfolg allein beweist keine Leckfreiheit; Freigabereihenfolge beachten.

## Einheit 20 – Opaque Type
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Opaque Type](../refactoring/opaque-type/README.md). Implementierungsdetails hinter einer C-Modulschnittstelle verbergen. **Ablauf:** 20 min Header-/Moduldesign, 40 min Umsetzung/Test, 15 min Diskussion. **Hinweis:** C90 ohne OOP; Sichtbarkeit, Lebenszyklus und API-Stabilität betrachten.

## Einheit 21 – Make Ownership Explicit
**Priorität:** optional · **Dauer:** 75 min

**Übung:** [Make Ownership Explicit](../refactoring/make-ownership-explicit/README.md). Owned/Borrowed Pointer, Freigabeverantwortung und Lebenszyklus verdeutlichen. **Ablauf:** 20 min Ownership-Vertrag, 40 min Umsetzung/Test, 15 min Review. **Hinweis:** Gemeinsame Tests allein beweisen keine korrekte Speicherverwaltung; Valgrind ergänzend einsetzen.

## Einheit 22 – Gesamtreview und Transfer
**Priorität:** optional · **Dauer:** 45 min

**Übung:** Eigenen oder bereitgestellten C90-Code in Kleingruppen prüfen: zwei Smells priorisieren, eine Verbesserung auswählen, Verhalten absichern, Metriken und Grenzen diskutieren. **Ablauf:** 10 min Aufgabenstellung, 25 min Gruppenarbeit, 10 min Ergebnisse. **Hinweis:** Nicht jedes Problem muss sofort refaktoriert werden.

---

## Moderationshinweise und Reihenfolge

**Empfohlene Reihenfolge:** 00–08 als durchgängiger Pflichtpfad. Die isolierten Refactoring-Übungen 09–21 sind modular: 09/12 passen nach Einheit 04, 11/15 nach Einheit 05, 10 nach Einheit 03, 16–21 nach Einheit 07 oder 08. Einheit 22 eignet sich als Abschluss eines längeren Trainings.

**Zeitreserve:** Die Angaben enthalten typische Diskussionen und Testläufe, aber keine längeren Infrastrukturprobleme. Für eine unerfahrene Gruppe oder eine neue Trainingsumgebung 10–20 % Reserve vorsehen.

**Beurteilung:** Nicht nur auf sinkende CCN/NLOC schauen. Erfolgreiche Verhaltensprüfung, verständliche Verantwortlichkeiten, begründete Entscheidungen und erkannte Grenzen der Metriken sind die zentralen Erfolgskriterien.

**Zweitagesvariante:** 16 h mandatory sind bereits mehr als zwei übliche Seminartage mit je etwa 6 h Netto-Unterricht. Für ein echtes Zweitagesformat müsste der Pflichtpfad bewusst gestrafft und mindestens ein Teil als Demonstration oder Selbstlernmaterial umgesetzt werden; diese Planung ist hier ausdrücklich **nicht** vorgenommen.
