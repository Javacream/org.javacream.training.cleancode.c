# Refactoring nach Fowler – Adaption für C

Sammlung von 13 eigenständig kompilierbaren Refactoring-Beispielen in C90. Die Verzeichnisse `before` und `after` enthalten jeweils ein vollständiges Minimalprogramm. Zu jedem Refactoring gibt es eine kurze Beschreibung.

## Struktur

`refactoring/<name>/README.md` – Erklärung

`refactoring/<name>/before/` – Ausgangscode

`refactoring/<name>/after/` – verbesserter Code

## Didaktische Auswahl für zwei Seminartage

Die acht Seminarblöcke bilden den **Pflicht-Lernpfad**. Die 13 Refactoring-Beispiele sind ein ergänzender Übungskatalog und müssen nicht vollständig bearbeitet werden. Für angeleitete Übungen bieten sich **Extract Function**, **Guard Clauses** und **Replace Magic Number** an; sie knüpfen unmittelbar an die Blöcke 03 bis 05 an. Je nach Lerngruppe kann eine dieser Übungen durch **Split Phase** ersetzt werden.

**Vertiefung/Wahlaufgaben:** Introduce Parameter Object, Split Phase, Replace Parallel Arrays, Replace Conditional with Dispatch, Encapsulate Global Variable, Global State to Context, Replace Error Sentinel, Extract Resource Cleanup, Opaque Type und Make Ownership Explicit. Besonders die letzten vier eignen sich für C-spezifische Vertiefung und die Diskussion von API-Verträgen, Ressourcen und Ownership.

Die Einordnung ist eine **Seminarempfehlung**, keine technische Unterscheidung: Alle 13 Beispiele bleiben einzeln ausführbar und werden durch das zentrale `make test` geprüft. Die Auswahl wird nach Vorwissen und verfügbarer Zeit getroffen.

## Beispiele

- [Extract Function](extract-function/README.md)
- [Introduce Parameter Object](introduce-parameter-object/README.md)
- [Replace Nested Conditional with Guard Clauses](guard-clauses/README.md)
- [Replace Conditional with Dispatch Table](replace-conditional-with-dispatch/README.md)
- [Split Phase](split-phase/README.md)
- [Replace Magic Number with Named Constant](replace-magic-number/README.md)
- [Replace Parallel Arrays with Array of Structs](replace-parallel-arrays/README.md)
- [Replace Error Sentinel with Status and Output](replace-error-sentinel/README.md)
- [Extract Resource Cleanup](extract-resource-cleanup/README.md)
- [Global State to Context](global-state-to-context/README.md)
- [Encapsulate Variable in Module](encapsulate-global-variable/README.md)
- [Expose Implementation to Opaque Type](opaque-type/README.md)
- [Make Ownership Explicit](make-ownership-explicit/README.md)

## Kompilieren

Im jeweiligen `before`- oder `after`-Verzeichnis:

```sh
make          # kompiliert alle .c-Dateien im Verzeichnis
make run      # startet das Beispiel
make test     # führt die gemeinsamen Verhaltenstests aus; in drei after-Varianten zusätzlich Contract-Tests
make clean    # entfernt die Build-Artefakte
```

## Einordnung

Die Beispiele sind didaktisch reduziert, keine produktionsfertigen Bibliotheken. Manche Änderungen (z. B. API-Signaturen, Ownership) erfordern Migration der Aufrufer und sind nicht isoliert verhaltensneutral. Die Ausgabe der jeweiligen Vorher-/Nachher-Programme wurde verglichen. Der Vergleich allein ersetzt keine Charakterisierungstests.

## Sprachstandard

Alle Beispiele sind ANSI-C90-konform. Die Makefiles verwenden `-std=c90 -pedantic-errors`. In `extract-resource-cleanup` wird `sprintf` nur mit einem fest dimensionierten 64-Byte-Puffer und einem `int` verwendet; für allgemeine Formatierungsaufgaben ist eine begrenzte Ausgabe vorzuziehen, die C90 nicht standardisiert bereitstellt.

## Unit-Tests (C90)

Jedes Refactoring besitzt genau eine gemeinsame `test.c` im Themenverzeichnis. Diese Datei wird unverändert für `before` und `after` verwendet. Unterschiedliche APIs werden durch `before/test_adapter.h` und `after/test_adapter.h` angeglichen. Im jeweiligen Variantenverzeichnis `make test` ausführen. `make clean` entfernt auch die Testdateien. Tests verwenden nur C90 und die Standardbibliothek, kein externes Framework.
