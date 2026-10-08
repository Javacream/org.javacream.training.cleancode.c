# Global State to Context

## Lernziele

Nach dieser Übung können die Teilnehmenden:
- die versteckte Abhängigkeit vom globalen Zähler aufzeigen;
- erklären, wie Kontextübergabe den Lebenszyklus und die Testbarkeit verändert;
- das bisherige Zählverhalten sowie die Unabhängigkeit zweier Kontexte unterscheiden und prüfen.

## Fachlicher Hintergrund und Abgrenzung

**Code Smell:** Globaler Zähler verhindert unabhängige Instanzen.

**Refactoring-Technik:** Zustand in einer explizit übergebenen Kontextstruktur halten.

Die öffentliche API ändert sich; die Migration der Aufrufer ist Teil der Aufgabe. Die Unabhängigkeit zweier Kontexte ist eine zusätzliche Eigenschaft der neuen Schnittstelle.

Die Technik ist eine mögliche Antwort auf ein konkretes Problem, keine allgemeine Pflicht. Beurteilen Sie auch, ob eine Änderung im gegebenen Kontext überhaupt sinnvoll ist.

## Ausgangssituation und Verhaltensvertrag

- [`before/`](before/): Ausgangsimplementierung.
- [`after/`](after/): Referenzimplementierung.
- [`test.c`](test.c): gemeinsame Verhaltenstests, die **unverändert** für beide Varianten eingesetzt werden.
- `before/test_adapter.h` und `after/test_adapter.h`: Anpassung unterschiedlicher Schnittstellen an die gemeinsamen Tests.

Die gemeinsamen Tests prüfen ausgewählte fachliche Ergebnisse und Randfälle; sie beweisen keine vollständige Verhaltensäquivalenz. Änderungen an öffentlichen APIs, neuen Eigenschaften oder Fehlerverträgen müssen zusätzlich ausdrücklich bewertet und gegebenenfalls durch eigene Vertragstests abgesichert werden.

## Aufgabenstellung

1. Lesen Sie zunächst `before`. Markieren Sie das konkrete Problem und beschreiben Sie das erwartete Verhalten.
2. Führen Sie im Verzeichnis `before` `make test` aus und halten Sie das Ergebnis fest.
3. Entscheiden Sie, ob die vorgeschlagene Technik für dieses Beispiel angemessen ist. Begründen Sie Ihre Wahl.
4. Führen Sie die Transformation in einer eigenen Arbeitskopie in kleinen, überprüfbaren Schritten durch. Vergleichen Sie erst anschließend mit `after`.
5. Führen Sie im Verzeichnis `after` `make test` aus. Prüfen Sie zusätzliche API-Verträge dort, wo die Implementierung dafür eigene Tests vorsieht.
6. Vergleichen Sie Verständlichkeit, Abhängigkeiten, Schnittstellen und Risiken der beiden Varianten.

## Erfolgskriterien

- Das Ausgangsproblem ist an mindestens einer konkreten Codefundstelle erklärt.
- Die gewählte Transformation ist anhand des Problems begründet; mögliche Nachteile sind benannt.
- Beide Varianten lassen sich im C90-Modus bauen und bestehen ihre vorhandenen gemeinsamen Verhaltenstests.
- Die für dieses Beispiel relevante fachliche oder technische Besonderheit wird nachvollziehbar erläutert.
- Etwaige API- oder Vertragsänderungen werden **nicht** als rein verhaltensneutrales Refactoring dargestellt.

## Reflexion

Welche Vorteile hat der Kontext gegenüber der bloßen Kapselung einer globalen Variablen?

## Durchführung und Werkzeuge

Im jeweiligen Variantenverzeichnis:

```sh
make
make test
make clean
```

Die Makefiles verwenden C90-Compileroptionen. `make test` führt die vorhandenen Tests aus; `make clean` entfernt erzeugte Build-Artefakte. Die Beispiele sind didaktisch reduziert und keine produktionsfertigen Bibliotheken.
