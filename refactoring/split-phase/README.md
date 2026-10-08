# Split Phase

## Lernziele

Nach dieser Übung können die Teilnehmenden:
- Parsing und Fachlogik im Ausgangscode voneinander abgrenzen;
- eine verständliche Übergabe zwischen beiden Phasen entwerfen;
- Ergebnisse und bisheriges Fehlerverhalten anhand der Tests vergleichen.

## Fachlicher Hintergrund und Abgrenzung

**Code Smell:** Eingabeinterpretation und Berechnung sind ineinander verschränkt.

**Refactoring:** Parsing und Berechnung als getrennte Phasen gestalten.

Fehler bei ungültiger oder zu großer Eingabe dürfen nicht unbeabsichtigt verändert werden. Die Technik wird anhand des konkreten Problems beurteilt und nicht als allgemeine Pflicht verstanden.

## Ausgangssituation und Verhaltensvertrag

- [`before/`](before/): Ausgangsimplementierung.
- [`after/`](after/): Referenzimplementierung.
- [`test.c`](test.c): gemeinsame, in beiden Varianten unverändert verwendete Verhaltenstests.
- `before/test_adapter.h` und `after/test_adapter.h`: Adapter für die unterschiedlichen Implementierungen.

Die Tests prüfen ausgewählte fachliche Ergebnisse und Randfälle, beweisen jedoch keine vollständige Verhaltensäquivalenz. Änderungen an APIs und fachlichen Verträgen sind getrennt zu beurteilen.

## Aufgabenstellung

1. Untersuchen Sie zunächst `before` und markieren Sie die konkrete Problemstelle.
2. Führen Sie dort `make test` aus und notieren Sie das Ergebnis.
3. Begründen Sie die Auswahl der Technik und skizzieren Sie die erforderlichen Schritte.
4. Überarbeiten Sie den Code in einer eigenen Arbeitskopie in kleinen Schritten; vergleichen Sie erst danach mit `after`.
5. Führen Sie `make test` in `after` aus und beurteilen Sie Ergebnisse, Schnittstellen und mögliche Risiken.

## Erfolgskriterien

- Das Problem ist anhand einer konkreten Fundstelle erläutert.
- Die Änderung ist fachlich begründet und mögliche Nachteile sind benannt.
- Beide Varianten bestehen die vorhandenen gemeinsamen Tests im C90-Modus.
- Die Besonderheit des Beispiels und die Grenzen des Verhaltensnachweises werden erklärt.

## Reflexion

Welche Phase sollte die Verantwortung für fehlerhafte Eingaben tragen?

## Durchführung

Im jeweiligen Variantenverzeichnis:

```sh
make
make test
make clean
```

Die Beispiele sind bewusst reduziert und keine produktionsfertigen Bibliotheken.
