# Block 07 – Testbarer Code und Clean Tests

## Lernziele
Nach diesem Block können die Teilnehmenden:
- Abhängigkeiten von globalem Zustand und Ein-/Ausgabe als Hindernisse für isolierte Tests identifizieren;
- eine reine Berechnung von Ein-/Ausgabe und globalem Zustand trennen und die verbesserte Testbarkeit erklären;
- mindestens einen zusätzlichen Testfall mit Eingabe, erwartetem Ergebnis und fachlicher Begründung formulieren;
- Normal-, Rand- und definierte ungewöhnliche Eingaben unterscheiden, ohne unbeabsichtigt neue Validierungsregeln einzuführen;
- die Aussagekraft und Grenzen einer mit `gcov` ermittelten Testabdeckung erläutern.

## Fachlicher Hintergrund und Abgrenzung
Die Ausgangsvariante koppelt globalen Steuersatz, Berechnung und Ausgabe. Die `clean`-Variante trennt Berechnung und I/O, verwendet ein separates Modul und testet definierte Fälle. Geldbeträge sind ganzzahlige Centwerte. Zusätzliche Eingabevalidierung ist eine **eigenständige fachliche Änderung** und nicht Teil eines verhaltensneutralen Refactorings. Ein möglicher Integer-Überlauf wird als Grenze des Beispiels besprochen, nicht stillschweigend durch neue Regeln verändert.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` und `clean/`. Die Berechnung muss für die bisher definierten Eingaben, auch ungewöhnliche, ihr Verhalten beibehalten. Die Dirty-Variante besitzt bewusst keine eigene Testsuite.

## Aufgabenstellung
1. Kennzeichnen Sie in `dirty` die Abhängigkeiten von globalem Zustand und Ausgabe.
2. Erklären Sie anhand von `clean`, warum die Fachlogik nun isoliert getestet werden kann.
3. Führen Sie im Clean-Verzeichnis die vorhandenen Tests und den Coverage-Lauf aus:

```sh
cd "clean"
make check
make coverage
```

4. Entwerfen und ergänzen Sie einen fachlich begründeten Testfall. Benennen Sie Eingabe, erwartetes Ergebnis und geprüfte Eigenschaft.
5. Diskutieren Sie, welche Fehler trotz hoher Abdeckung unentdeckt bleiben können.

## Erfolgskriterien
- Mindestens zwei konkrete Testbarkeitshindernisse der Ausgangsversion sind benannt.
- Ein zusätzlicher Testfall besitzt eine nachvollziehbare Erwartung und läuft erfolgreich.
- Die Trennung von Berechnung und I/O wird am Code erläutert.
- Coverage wird als Ausführungsmaß, nicht als Beweis der Testqualität interpretiert.
- Es werden keine unbeabsichtigten neuen Validierungsregeln eingeführt.

## Reflexion
Welche Testfälle wären für Grenzwerte besonders wichtig? Wie ließe sich ein möglicher Integer-Überlauf behandeln, ohne ihn als reines Refactoring auszugeben?

## Ergänzende Implementierungsübung: Rechteck

Im Verzeichnis [`exercise/`](exercise/) liegt eine von Beginn an sauber strukturierte C90-Anwendung zur Berechnung von Fläche und Umfang eines Rechtecks. `main` verwendet `a = 5` und `b = 37` (Fläche **185**, Umfang **84**). Die Berechnungen befinden sich in einem eigenen Modul und werden unabhängig von der Konsolenausgabe getestet.

```sh
cd exercise
make run
make test
```
