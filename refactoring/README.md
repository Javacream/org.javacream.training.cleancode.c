# Refactoring nach Fowler – Adaption für C

Sammlung von 13 eigenständig kompilierbaren Refactoring-Beispielen in C90. Die Verzeichnisse `before` und `after` enthalten jeweils ein vollständiges Minimalprogramm. Zu jedem Refactoring gibt es eine kurze Beschreibung.

## Struktur

`refactoring/<name>/README.md` – Erklärung

`refactoring/<name>/before/` – Ausgangscode

`refactoring/<name>/after/` – verbesserter Code

## Beispiele

- [Extract Function](refactoring/extract-function/README.md)
- [Introduce Parameter Object](refactoring/introduce-parameter-object/README.md)
- [Replace Nested Conditional with Guard Clauses](refactoring/guard-clauses/README.md)
- [Replace Conditional with Dispatch Table](refactoring/replace-conditional-with-dispatch/README.md)
- [Split Phase](refactoring/split-phase/README.md)
- [Replace Magic Number with Named Constant](refactoring/replace-magic-number/README.md)
- [Replace Parallel Arrays with Array of Structs](refactoring/replace-parallel-arrays/README.md)
- [Replace Error Sentinel with Status and Output](refactoring/replace-error-sentinel/README.md)
- [Extract Resource Cleanup](refactoring/extract-resource-cleanup/README.md)
- [Global State to Context](refactoring/global-state-to-context/README.md)
- [Encapsulate Variable in Module](refactoring/encapsulate-global-variable/README.md)
- [Expose Implementation to Opaque Type](refactoring/opaque-type/README.md)
- [Make Ownership Explicit](refactoring/make-ownership-explicit/README.md)

## Kompilieren

Im jeweiligen `before`- oder `after`-Verzeichnis:

```sh
make          # kompiliert alle .c-Dateien im Verzeichnis
make run      # startet das Beispiel
make clean    # entfernt die Build-Artefakte
```

## Einordnung

Die Beispiele sind didaktisch reduziert, keine produktionsfertigen Bibliotheken. Manche Änderungen (z. B. API-Signaturen, Ownership) erfordern Migration der Aufrufer und sind nicht isoliert verhaltensneutral. Die Ausgabe der jeweiligen Vorher-/Nachher-Programme wurde verglichen. Der Vergleich allein ersetzt keine Charakterisierungstests.

## Sprachstandard

Alle Beispiele sind ANSI-C90-konform. Die Makefiles verwenden `-std=c90 -pedantic-errors`. In `extract-resource-cleanup` wird `sprintf` nur mit einem fest dimensionierten 64-Byte-Puffer und einem `int` verwendet; für allgemeine Formatierungsaufgaben ist eine begrenzte Ausgabe vorzuziehen, die C90 nicht standardisiert bereitstellt.
