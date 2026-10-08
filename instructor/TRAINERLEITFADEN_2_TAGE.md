# Kompakter Trainerleitfaden – Clean Code mit C90 (2 Tage)

**Stand:** 09.11.2026  
**Dauer:** 2 × 360 Minuten = **12 Stunden Netto-Unterricht**; Pausen zusätzlich  
**Voraussetzungen:** C-Grundkenntnisse, VS Code und funktionsfähiger Devcontainer  
**Ausführliche Referenz:** [Trainerleitfaden – vollständiger Lernpfad](TRAINERLEITFADEN.md)  
**Prioritäten:** **mandatory** = für diese Zweitagesdurchführung verbindlich; **optional** = Reserve, Demonstration oder Selbststudium.

## Didaktische Leitlinie

Die zwei Tage sind ein **bewusst ausgewählter Praxispfad**, nicht die vollständige Durchführung aller Aufgaben aus den Block-READMEs. Für die mandatory-Übungen sind unten jeweils konkrete Mindestaufgaben definiert. Die `dirty`-Variante wird zuerst untersucht, `clean` erst im Review gezeigt. Änderungen am beobachtbaren Verhalten sind durch Ausgaben oder Tests abzusichern. Die gemeinsame Testumgebung muss vor Seminarbeginn überprüft sein.

## Zeitplan auf einen Blick

| Tag | Einheit | Thema | Priorität | Dauer |
|---|---|---|---|---:|
| 1 | 00 | Arbeitsumgebung und Vorgehen | mandatory | 20 min |
| 1 | 01 | Clean-Code-Grundlagen | mandatory | 45 min |
| 1 | 02 | Code Smells erkennen und priorisieren | mandatory | 55 min |
| 1 | 03 | Namen und Datentypen | mandatory | 55 min |
| 1 | 04 | Funktionen und Verantwortlichkeiten | mandatory | 100 min |
| 1 | 05 | Kontrollfluss und Guard Clauses | mandatory | 85 min |
| **Tag 1** | | **Summe** | | **360 min** |
| 2 | 06 | Metriken und statische Codeanalyse | mandatory | 70 min |
| 2 | 07 | Testbarkeit und Clean Tests | mandatory | 110 min |
| 2 | 08 | Refactoring in kleinen Schritten | mandatory | 150 min |
| 2 | 09 | Abschluss und Transfer | mandatory | 30 min |
| **Tag 2** | | **Summe** | | **360 min** |
| – | V1 | Weitere isolierte Refactoring-Techniken | optional | außerhalb der 12 h |
| – | V2 | Vertiefte ADR-/Architekturdiskussion | optional | außerhalb der 12 h |

**Zeitmodell:** Jede mandatory-Einheit umfasst Einführung, Demonstration, Arbeitsphase, Ergebnisvergleich und Rückfragen. Es ist **keine zusätzliche freie Übungszeit** in den zwölf Stunden eingeplant. Die im Folgenden genannten Phasen summieren sich exakt auf die Einheitsdauer.

---

# Tag 1 – Verständlicher Code und Struktur

## Einheit 00 – Arbeitsumgebung und Vorgehen
**Priorität: mandatory · 20 min**

**Ziel:** Alle Teilnehmenden können im Devcontainer bauen und Tests ausführen.

**Ablauf:** 5 min Ziel und Arbeitsweise; 10 min Devcontainer/VS-Code-Demo; 5 min eigener Smoke-Test.

**Präsentation:** [Projekt-README](../README.md), `.devcontainer/`, `.vscode/tasks.json`. Beispiel `blocks/01-grundlagen/dirty/` öffnen, `make` und `make test` demonstrieren.

**Trainerhinweis:** Umgebung möglichst vorab bereitstellen; bei individuellen Setup-Problemen vorbereitete Umgebung verwenden, statt die fachliche Agenda zu verdrängen.

## Einheit 01 – Clean-Code-Grundlagen und Prinzipien
**Priorität: mandatory · 45 min**

**Ziel:** Lesbarkeit, Wartbarkeit und Testbarkeit unterscheiden; KISS, DRY und YAGNI kontextabhängig anwenden.

**Ablauf:** 15 min Theorie; 10 min Trainerdemonstration; 15 min Partneranalyse; 5 min Auswertung.

**Übung:** [Block 01](../blocks/01-grundlagen/README.md). `dirty/main.c` und `dirty/doc.md` untersuchen, **zwei** konkrete Verständnishürden benennen; anschließend `clean/main.c` vergleichen. Welche Aussagen der Dokumentation werden durch Code verständlich, welche bleiben wichtig?

**Bewusste Kürzung:** ADR-Aufbau, technische Schulden und Teamprozesse nur kurz einordnen; keine eigene ADR-Schreibübung.

## Einheit 02 – Code Smells erkennen und priorisieren
**Priorität: mandatory · 55 min**

**Ziel:** Smell und Bug unterscheiden, Befunde begründen und priorisieren.

**Ablauf:** 15 min Einführung und Matrix; 25 min Partnerübung; 15 min Auswertung.

**Übung:** [Block 02](../blocks/02-code-smells/README.md) und [Code-Smell-/Refactoring-Matrix](../CODE-SMELL-REFACTORING-MATRIX.md). **Drei** konkrete Smells in `dirty/main.c` markieren, **einen** priorisieren und eine mögliche Refactoring-Technik zuordnen. Referenz `clean` erst zum Schluss zeigen.

**Bewusste Kürzung:** Kein vollständiges Refactoring sämtlicher Smells; Fokus auf Diagnose und Entscheidung.

## Einheit 03 – Namen, Datentypen und Ausdruckskraft
**Priorität: mandatory · 55 min**

**Ziel:** Aussagekräftige Bezeichner und geeignete C90-Typen einsetzen.

**Ablauf:** 15 min `enum`, `unsigned int` und boolesche Darstellung in C90; 25 min Übung; 15 min Ergebnisvergleich.

**Übung:** [Block 03](../blocks/03-namen-datentypen/README.md). Mindestens **zwei** unklare Namen oder Typentscheidungen verbessern. Die vier in der README dokumentierten Eingabekombinationen zum Vergleich verwenden.

**Trainerhinweis:** Die CCN muss sich hier nicht verbessern; keine vorgezogene Funktionszerlegung.

## Einheit 04 – Funktionen und Verantwortlichkeiten
**Priorität: mandatory · 100 min**

**Ziel:** Validierung, Berechnung und Ausgabe trennen; Funktionsgrenzen und Parameter begründen.

**Ablauf:** 20 min Prinzipien und Live-Analyse; 15 min Entwurf; 45 min Umsetzung; 20 min Test und Review.

**Übung:** [Block 04](../blocks/04-funktionen/README.md). In `dirty/main.c` Verantwortlichkeiten markieren und mindestens **eine fachlich sinnvolle Funktion** extrahieren; `print_details = 0` und `print_details = 1` prüfen. `clean/main.c` als Referenz.

**Kurzdemonstration innerhalb der Einheit:** [Extract Function](../refactoring/extract-function/README.md) als Technik und Verhaltensvertrag vorstellen, **keine zweite vollständige Übung**.

**Trainerhinweis:** Die Qualität der Funktionsgrenzen ist wichtiger als eine möglichst große Zahl kleiner Funktionen.

## Einheit 05 – Kontrollfluss und Guard Clauses
**Priorität: mandatory · 85 min**

**Ziel:** Normal- und Fehlerpfade trennen und Verschachtelung reduzieren.

**Ablauf:** 20 min Guard Clauses/`switch`; 15 min Pfadanalyse; 35 min Umsetzung; 15 min Test und Vergleich.

**Übung:** [Block 05](../blocks/05-kontrollfluss/README.md). Mindestens **einen verschachtelten Fehlerpfad** in `dirty/main.c` durch eine Guard Clause strukturieren; mindestens einen gültigen und zwei ungültige Fälle einschließlich Fehlercodes prüfen. `clean` vergleichen.

**Kurzdemonstration:** [Guard Clauses](../refactoring/guard-clauses/README.md) nur bei Bedarf als ergänzendes Muster zeigen.

**Trainerhinweis:** Unveränderte CCN bei geringerer Verschachtelung ausdrücklich hervorheben.

---

# Tag 2 – Messen, Testen und Refactoring

## Einheit 06 – Metriken und statische Codeanalyse
**Priorität: mandatory · 70 min**

**Ziel:** CCN, NLOC, Verschachtelung und Cppcheck als Indikatoren interpretieren, ohne daraus einen pauschalen Qualitätsscore abzuleiten.

**Ablauf:** 20 min Kennzahlen; 15 min Bericht erzeugen und erläutern; 20 min Kleingruppenvergleich; 15 min Diskussion.

**Übung:** [Block 06](../blocks/06-metriken/README.md), [Qualitätsbericht](../quality-report.md). Ausführen:

```sh
python3 analyze.py --output quality-report.md
make -C blocks/06-metriken/clean compare
```

In der Gruppe **Block 05 und 06** vergleichen: Wo sinkt die CCN, wo nur die Verschachtelung? Zusätzlich einen Cppcheck-Befund aus dem Gesamtbericht fachlich einordnen.

**Bewusste Kürzung:** Keine vollständige Werkzeugschulung; alternative Implementierung nur bei verbleibender Zeit diskutieren.

## Einheit 07 – Testbarkeit und Clean Tests
**Priorität: mandatory · 110 min**

**Ziel:** Logik von I/O und globalem Zustand trennen und die Wirkung auf isolierte Tests verstehen.

**Ablauf:** 20 min Testbarkeit; 20 min Vergleich `dirty`/`clean`; 45 min eigenen Testfall ergänzen; 15 min Coverage-Demo; 10 min Diskussion.

**Übung:** [Block 07](../blocks/07-testbarkeit/README.md), insbesondere `dirty/main.c`, `clean/logic.c` und `clean/test.c`. In `blocks/07-testbarkeit/clean/`:

```sh
make check
make coverage
```

Mindestens **einen zusätzlichen fachlich begründeten Testfall** schreiben und ausführen.

**Trainerhinweis:** Coverage misst Ausführung, nicht Testqualität. Keine neuen Validierungsregeln als Refactoring einführen.

## Einheit 08 – Refactoring in kleinen, abgesicherten Schritten
**Priorität: mandatory · 150 min**

**Ziel:** Den vollständigen Zyklus Smell → Plan → kleiner Schritt → Test → nächster Schritt nachvollziehen.

**Ablauf:** 20 min Refactoring-Prinzip und Verhaltenserhaltung; 20 min Smells priorisieren/Plan erstellen; 75 min eigenständige Umsetzung mit Tests nach jedem Schritt; 25 min Referenzvergleich; 10 min Reflexion.

**Übung:** [Block 08](../blocks/08-refactoring/README.md), `dirty/logic.c` und vorhandene Charakterisierungstests. Zuerst `make check`; anschließend **zwei getrennte Verbesserungen** (z. B. benannte Konstante, Extract Function oder Guard Clause), jeweils mit erneuter Testausführung. Erst danach mit `clean` vergleichen.

**Trainerhinweis:** Diese Einheit nicht zugunsten zusätzlicher isolierter Refactoring-Beispiele kürzen. Mehrere sinnvolle Lösungen zulassen; keine fachlichen Änderungen verstecken.

## Einheit 09 – Abschluss, Review und Transfer
**Priorität: mandatory · 30 min**

**Ziel:** Den Transfer auf reale C-Projekte vorbereiten.

**Ablauf:** 15 min gemeinsames Review einer Änderung aus Block 08; 10 min Diskussion über Testgrenzen, Metriken und technische Schulden; 5 min persönliche nächste Schritte.

**Übung:** Eine konkrete Verbesserung anhand von Verständlichkeit, Verhaltensprüfung und Änderungsrisiko verteidigen. Keine zusätzliche Programmieraufgabe.

---

# Optionale Vertiefungen – nicht im Zweitagesbudget enthalten

## V1 – Eigenständige Refactoring-Techniken
**Priorität: optional · zusätzlich 30–75 min pro Technik**

Die [13 Refactoring-Beispiele](../refactoring/README.md) sind als Wahlaufgaben oder Material für einen Aufbaukurs vorgesehen. Für schnelle Vertiefungen eignen sich [Replace Magic Number](../refactoring/replace-magic-number/README.md) (30 min), [Extract Function](../refactoring/extract-function/README.md) (45 min) und [Guard Clauses](../refactoring/guard-clauses/README.md) (45 min). Für erfahrene C-Entwickler bieten sich [Global State to Context](../refactoring/global-state-to-context/README.md), [Extract Resource Cleanup](../refactoring/extract-resource-cleanup/README.md) und [Make Ownership Explicit](../refactoring/make-ownership-explicit/README.md) an (je 75 min).

Die drei genannten C-spezifischen Vertiefungen können zusätzliche API-Verträge, Ressourcenverwaltung oder Ownership behandeln. Solche Änderungen nicht pauschal als verhaltensneutrales Refactoring ausgeben.

## V2 – Architekturentscheidungen und technische Schulden
**Priorität: optional · zusätzlich 45–60 min**

[Block 01](../blocks/01-grundlagen/README.md) vertiefen: ADR mit Kontext, Alternativen, Entscheidung und Konsequenzen skizzieren; technische Schulden von bewussten Architekturkompromissen unterscheiden.

## Hinweise für den Trainer

- **Vorbereitung:** Devcontainer starten, `make clean test` im Projektwurzelverzeichnis prüfen und Qualitätsbericht vorab generieren; Referenzlösungen verfügbar halten.
- **Arbeitsform:** Kurze Impulse, überwiegend Paararbeit, danach gemeinsamer Vergleich; keine vollständigen `clean`-Lösungen vor der Übung präsentieren.
- **Zeitsteuerung:** Nach den vorgesehenen Arbeitsphasen konsequent in das Review wechseln. Bei Verzögerungen den **Umfang innerhalb der Übung** reduzieren, nicht die Verhaltensprüfung auslassen.
- **Abgrenzung:** Die im vollständigen Trainerleitfaden enthaltenen weiteren Refactorings sind **nicht Teil des Pflichtprogramms**.
- **Grenze der Planung:** Die zwölf Stunden sind ein realistischer, aber straffer Zuschnitt für Teilnehmende mit C-Erfahrung. Setup-Probleme oder deutlich unterschiedliche Vorkenntnisse benötigen zusätzliche Zeit bzw. vorab bereitgestellte Arbeitsumgebungen.
