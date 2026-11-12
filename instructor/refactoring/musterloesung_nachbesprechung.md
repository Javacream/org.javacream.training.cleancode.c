# Musterlösung und Nachbesprechung – Refactoring-Beispiele (C90)

> **Trainerunterlage.** Referenz: [`refactoring/`](../../refactoring/) im Branch `training`. Die folgenden Erläuterungen beziehen sich auf die vorhandenen `before`- und `after`-Varianten, nicht auf eine allgemeine Musterimplementierung.

## Durchführung und Bewertungsmaßstab

Die Beispiele dienen dem Vergleich einer konkreten Ausgangssituation mit einer gezielten Refactoring-Technik. Eine Musterlösung ist **keine Verpflichtung**, jedes ähnliche Problem auf dieselbe Weise zu lösen. Entscheidend sind nachvollziehbare Verantwortlichkeiten, beherrschbare Schnittstellen und unveränderte beziehungsweise ausdrücklich neu definierte Verträge.

Für jedes Beispiel:

1. `before` untersuchen und den Code Smell an einer Fundstelle erläutern.
2. In `before` `make test` ausführen.
3. Die Veränderung anhand der nachfolgenden Hinweise nachvollziehen und mit `after` vergleichen.
4. In `after` `make test` ausführen; vorhandene zusätzliche Vertragstests beachten.
5. Nutzen, neue Abhängigkeiten, API-Änderungen und verbleibende Risiken diskutieren.

Die gemeinsame Datei `refactoring/<name>/test.c` wird über `before/test_adapter.h` beziehungsweise `after/test_adapter.h` an die Implementierungen gebunden. **Bestehende Verhaltenstests belegen nur die getesteten Fälle, nicht vollständige Äquivalenz.**

## Übersicht

| Beispiel | Ausgangsproblem | Wesentliche Änderung |
|---|---|---|
| [encapsulate-global-variable](../../refactoring/encapsulate-global-variable/) | Der globale Kontostand ist direkt zugreifbar und damit von beliebigen Aufrufern veränderbar. | Encapsulate Variable in Module |
| [extract-function](../../refactoring/extract-function/) | Die Rechnungsfunktion vermischt Summierung der Positionen und Steuerberechnung. | Extract Function |
| [extract-resource-cleanup](../../refactoring/extract-resource-cleanup/) | Datei und dynamischer Puffer müssen auf mehreren Erfolgs- und Fehlerpfaden freigegeben werden. | Extract Resource Cleanup |
| [global-state-to-context](../../refactoring/global-state-to-context/) | Ein globaler Zähler koppelt alle Aufrufer an dieselbe Instanz. | Global State to Context |
| [guard-clauses](../../refactoring/guard-clauses/) | Mehrfach verschachtelte Validierungen verdecken den normalen Ablauf von `process()`. | Replace Nested Conditional with Guard Clauses |
| [introduce-parameter-object](../../refactoring/introduce-parameter-object/) | Zusammengehörige Versand- und Tarifwerte werden als lange Liste einzelner Parameter übergeben. | Introduce Parameter Object |
| [make-ownership-explicit](../../refactoring/make-ownership-explicit/) | Aus der ursprünglichen Schnittstelle geht nicht zuverlässig hervor, wer den allokierten Speicher freigibt. | Make Ownership Explicit |
| [opaque-type](../../refactoring/opaque-type/) | Ein öffentlich sichtbares `struct Counter` erlaubt direkte Feldzugriffe und bindet Aufrufer an die Repräsentation. | Expose Implementation to Opaque Type |
| [replace-conditional-with-dispatch](../../refactoring/replace-conditional-with-dispatch/) | Eine Fallunterscheidung wählt anhand von `ShippingType` zwischen mehreren gleichartig signierten Berechnungen. | Replace Conditional with Dispatch Table |
| [replace-error-sentinel](../../refactoring/replace-error-sentinel/) | Ein spezieller numerischer Fehlerwert kann mit einem fachlich gültigen Ergebnis kollidieren. | Replace Error Sentinel with Status and Output |
| [replace-magic-number](../../refactoring/replace-magic-number/) | Die Mehrwertsteuerrate `0.19` erscheint ohne benannte fachliche Bedeutung in mehreren Berechnungen. | Replace Magic Number with Named Constant |
| [replace-parallel-arrays](../../refactoring/replace-parallel-arrays/) | Preis und Menge sind nur durch denselben Index in getrennten Arrays verbunden. | Replace Parallel Arrays with Array of Structs |
| [split-phase](../../refactoring/split-phase/) | Die Funktion vermischt das Interpretieren eines Eingabestrings mit der fachlichen Bruttoberechnung. | Split Phase |

## Musterlösungen

### 1. Encapsulate Variable in Module (`encapsulate-global-variable`)

**Code Smell / Ausgangslage:** Der globale Kontostand ist direkt zugreifbar und damit von beliebigen Aufrufern veränderbar.

**Musterlösung:** `account_deposit()` und `account_get_balance()` kapseln den Zustand in einem Modul. Der Aufrufer benötigt keinen direkten Zugriff mehr auf die Variable.

**Bewertung und Fallstricke:** Kapselung verhindert unkontrollierte externe Schreibzugriffe, beseitigt aber nicht den globalen Zustand. Es bleibt genau ein gemeinsames Konto.

**Nachbesprechung:** Würde eine Anwendung mehrere unabhängige Konten benötigen, wäre ein expliziter Kontext oder ein Account-Objekt in C geeigneter.

**Quellen im Repository:** [Beschreibung](../../refactoring/encapsulate-global-variable/README.md) · [Before](../../refactoring/encapsulate-global-variable/before/) · [After](../../refactoring/encapsulate-global-variable/after/) · [Gemeinsame Tests](../../refactoring/encapsulate-global-variable/test.c)

### 2. Extract Function (`extract-function`)

**Code Smell / Ausgangslage:** Die Rechnungsfunktion vermischt Summierung der Positionen und Steuerberechnung.

**Musterlösung:** Die statische Hilfsfunktion `subtotal(prices, count)` berechnet den Nettobetrag; `invoice_total()` addiert anschließend die Steuer.

**Bewertung und Fallstricke:** Berechnungsreihenfolge und `double`-Arithmetik bleiben erhalten. Die neue Funktion ist intern (`static`) und erweitert die öffentliche API nicht.

**Nachbesprechung:** Ist die extrahierte Funktion fachlich verständlich benannt und eigenständig testbar, oder wird lediglich Code verschoben?

**Quellen im Repository:** [Beschreibung](../../refactoring/extract-function/README.md) · [Before](../../refactoring/extract-function/before/) · [After](../../refactoring/extract-function/after/) · [Gemeinsame Tests](../../refactoring/extract-function/test.c)

### 3. Extract Resource Cleanup (`extract-resource-cleanup`)

**Code Smell / Ausgangslage:** Datei und dynamischer Puffer müssen auf mehreren Erfolgs- und Fehlerpfaden freigegeben werden.

**Musterlösung:** Ein gemeinsamer `cleanup`-Abschnitt gibt den Puffer frei und schließt die Datei. Bei Fehlern wird über `goto cleanup` dorthin verzweigt.

**Bewertung und Fallstricke:** `buffer` wird erst nach erfolgreichem `malloc` verwendet; `free(NULL)` wäre zulässig, aber die Initialisierung muss stets definiert sein. `fclose()` kann selbst fehlschlagen und muss den Rückgabestatus beeinflussen. Tests beweisen keine Leckfreiheit.

**Nachbesprechung:** Warum ist ein gezieltes `goto cleanup` in C häufig verständlicher als viele duplizierte Freigaben?

**Quellen im Repository:** [Beschreibung](../../refactoring/extract-resource-cleanup/README.md) · [Before](../../refactoring/extract-resource-cleanup/before/) · [After](../../refactoring/extract-resource-cleanup/after/) · [Gemeinsame Tests](../../refactoring/extract-resource-cleanup/test.c)

### 4. Global State to Context (`global-state-to-context`)

**Code Smell / Ausgangslage:** Ein globaler Zähler koppelt alle Aufrufer an dieselbe Instanz.

**Musterlösung:** `MetricsContext` enthält `requests`; `record_request(ctx)` und `request_count(ctx)` erhalten einen Kontextzeiger.

**Bewertung und Fallstricke:** Die API ändert sich; alle Aufrufer müssen den Kontext erzeugen und weiterreichen. Zwei Kontexte können unabhängig zählen – eine zusätzliche Eigenschaft, die separat getestet werden sollte.

**Nachbesprechung:** Wie werden Initialisierung, Lebensdauer, Nullzeiger und gegebenenfalls Nebenläufigkeit geregelt?

**Quellen im Repository:** [Beschreibung](../../refactoring/global-state-to-context/README.md) · [Before](../../refactoring/global-state-to-context/before/) · [After](../../refactoring/global-state-to-context/after/) · [Gemeinsame Tests](../../refactoring/global-state-to-context/test.c)

### 5. Replace Nested Conditional with Guard Clauses (`guard-clauses`)

**Code Smell / Ausgangslage:** Mehrfach verschachtelte Validierungen verdecken den normalen Ablauf von `process()`.

**Musterlösung:** Die Funktion prüft `o == NULL`, `o->items == NULL` und `o->count == 0` mit frühen Rückgaben; danach bleibt der Normalfall linear.

**Bewertung und Fallstricke:** Die Prüfungsreihenfolge ist relevant: Vor `o->items` muss `o` auf Null geprüft werden. Der Fehlerwert `-1` und der gültige Rückgabewert (Anzahl) bleiben erhalten.

**Nachbesprechung:** Wann sind mehrere frühe Rückgaben hilfreich, und wann erschweren sie Ressourcenfreigabe?

**Quellen im Repository:** [Beschreibung](../../refactoring/guard-clauses/README.md) · [Before](../../refactoring/guard-clauses/before/) · [After](../../refactoring/guard-clauses/after/) · [Gemeinsame Tests](../../refactoring/guard-clauses/test.c)

### 6. Introduce Parameter Object (`introduce-parameter-object`)

**Code Smell / Ausgangslage:** Zusammengehörige Versand- und Tarifwerte werden als lange Liste einzelner Parameter übergeben.

**Musterlösung:** `Shipment` bündelt `weight` und `distance`, `Tariff` bündelt `base`, `per_km` und `per_kg`; `shipping()` akzeptiert Zeiger auf beide Strukturen.

**Bewertung und Fallstricke:** Die neue Signatur ist eine API-Änderung. Ein `const`-Zeiger dokumentiert, dass die Funktion die Werte nicht verändern soll. Die Formel und die Einheiten bleiben gleich.

**Nachbesprechung:** Sind die Parameter fachlich zusammengehörig, oder entsteht eine künstliche Struktur?

**Quellen im Repository:** [Beschreibung](../../refactoring/introduce-parameter-object/README.md) · [Before](../../refactoring/introduce-parameter-object/before/) · [After](../../refactoring/introduce-parameter-object/after/) · [Gemeinsame Tests](../../refactoring/introduce-parameter-object/test.c)

### 7. Make Ownership Explicit (`make-ownership-explicit`)

**Code Smell / Ausgangslage:** Aus der ursprünglichen Schnittstelle geht nicht zuverlässig hervor, wer den allokierten Speicher freigibt.

**Musterlösung:** `buffer_create()` liefert einen besessenen Zeiger; `buffer_destroy()` übernimmt die Freigabe. Der Kommentar dokumentiert die Ownership-Regel.

**Bewertung und Fallstricke:** `buffer_create()` kann `NULL` liefern; der Aufrufer muss diesen Fall prüfen. Die neue API verdeutlicht den Vertrag, garantiert aber nicht automatisch, dass alle Aufrufer ihn einhalten.

**Nachbesprechung:** Wer ist für Freigabe, doppelte Freigabe und Fehlerpfade verantwortlich? Welche Tests oder Speicheranalyse helfen?

**Quellen im Repository:** [Beschreibung](../../refactoring/make-ownership-explicit/README.md) · [Before](../../refactoring/make-ownership-explicit/before/) · [After](../../refactoring/make-ownership-explicit/after/) · [Gemeinsame Tests](../../refactoring/make-ownership-explicit/test.c)

### 8. Expose Implementation to Opaque Type (`opaque-type`)

**Code Smell / Ausgangslage:** Ein öffentlich sichtbares `struct Counter` erlaubt direkte Feldzugriffe und bindet Aufrufer an die Repräsentation.

**Musterlösung:** `counter.h` veröffentlicht einen unvollständigen Typ `Counter`; Erzeugung, Zugriff und Freigabe erfolgen über `counter_create()`, `counter_increment()`, `counter_value()` und `counter_destroy()`.

**Bewertung und Fallstricke:** Die Repräsentation wird privat, gleichzeitig verändert sich die Lebensdauer: Aufrufer arbeiten mit einem Zeiger und müssen ihn freigeben. Diese API-Migration ist nicht rein kosmetisch.

**Nachbesprechung:** Wann ist ein Opaque Type den zusätzlichen Allokations- und Funktionsaufrufen vorzuziehen?

**Quellen im Repository:** [Beschreibung](../../refactoring/opaque-type/README.md) · [Before](../../refactoring/opaque-type/before/) · [After](../../refactoring/opaque-type/after/) · [Gemeinsame Tests](../../refactoring/opaque-type/test.c)

### 9. Replace Conditional with Dispatch Table (`replace-conditional-with-dispatch`)

**Code Smell / Ausgangslage:** Eine Fallunterscheidung wählt anhand von `ShippingType` zwischen mehreren gleichartig signierten Berechnungen.

**Musterlösung:** Ein `Calculator`-Funktionszeiger und eine konstante Tabelle ordnen `STANDARD`, `EXPRESS` und `OVERNIGHT` den Funktionen `standard`, `express` und `overnight` zu.

**Bewertung und Fallstricke:** Vor dem Tabellenzugriff werden negative und zu große Typwerte abgefangen. Die Indizes müssen mit der Enum-Reihenfolge übereinstimmen; eine spätere Änderung kann die Zuordnung brechen.

**Nachbesprechung:** Ist die Tabelle bei drei Varianten klarer als ein kurzer `switch`? Wie lassen sich Enum-Werte und Tabelle dauerhaft synchron halten?

**Quellen im Repository:** [Beschreibung](../../refactoring/replace-conditional-with-dispatch/README.md) · [Before](../../refactoring/replace-conditional-with-dispatch/before/) · [After](../../refactoring/replace-conditional-with-dispatch/after/) · [Gemeinsame Tests](../../refactoring/replace-conditional-with-dispatch/test.c)

### 10. Replace Error Sentinel with Status and Output (`replace-error-sentinel`)

**Code Smell / Ausgangslage:** Ein spezieller numerischer Fehlerwert kann mit einem fachlich gültigen Ergebnis kollidieren.

**Musterlösung:** `parse_temperature(text, out)` liefert einen Erfolgsstatus und schreibt bei Erfolg den Wert über `out`; die Rückgabekanäle sind getrennt.

**Bewertung und Fallstricke:** Die öffentliche API und ihre Semantik ändern sich bewusst. Ein gültiger Wert `-9999` darf nicht mehr als Fehler missverstanden werden. Der gemeinsame Adapter kann diese Verbesserung verdecken; die neuen Vertragstests sind entscheidend.

**Nachbesprechung:** Wie verhalten sich die Funktion und der Ausgabeparameter bei ungültigem Text, `NULL` und einem gültigen negativen Wert?

**Quellen im Repository:** [Beschreibung](../../refactoring/replace-error-sentinel/README.md) · [Before](../../refactoring/replace-error-sentinel/before/) · [After](../../refactoring/replace-error-sentinel/after/) · [Gemeinsame Tests](../../refactoring/replace-error-sentinel/test.c)

### 11. Replace Magic Number with Named Constant (`replace-magic-number`)

**Code Smell / Ausgangslage:** Die Mehrwertsteuerrate `0.19` erscheint ohne benannte fachliche Bedeutung in mehreren Berechnungen.

**Musterlösung:** Die dateilokale Konstante `VAT_RATE` wird von `surcharge()` und `gross()` verwendet.

**Bewertung und Fallstricke:** Die Benennung erhöht Verständlichkeit und vermeidet divergierende Werte. Eine Konstante ist allerdings keine Lösung, wenn Steuersätze von Zeitpunkt oder Produkt abhängen.

**Nachbesprechung:** Soll der Wert im Code, in einer Konfiguration oder als Funktionsparameter liegen?

**Quellen im Repository:** [Beschreibung](../../refactoring/replace-magic-number/README.md) · [Before](../../refactoring/replace-magic-number/before/) · [After](../../refactoring/replace-magic-number/after/) · [Gemeinsame Tests](../../refactoring/replace-magic-number/test.c)

### 12. Replace Parallel Arrays with Array of Structs (`replace-parallel-arrays`)

**Code Smell / Ausgangslage:** Preis und Menge sind nur durch denselben Index in getrennten Arrays verbunden.

**Musterlösung:** `LineItem` enthält `price` und `quantity`; `total(items, n)` iteriert über ein Array dieser Strukturen.

**Bewertung und Fallstricke:** Die Zusammengehörigkeit wird strukturell abgesichert. Reihenfolge und Zuordnung der Datensätze müssen bei der Migration erhalten bleiben; die API wird geändert.

**Nachbesprechung:** Was geschieht, wenn nur eines der ursprünglichen Arrays sortiert wird?

**Quellen im Repository:** [Beschreibung](../../refactoring/replace-parallel-arrays/README.md) · [Before](../../refactoring/replace-parallel-arrays/before/) · [After](../../refactoring/replace-parallel-arrays/after/) · [Gemeinsame Tests](../../refactoring/replace-parallel-arrays/test.c)

### 13. Split Phase (`split-phase`)

**Code Smell / Ausgangslage:** Die Funktion vermischt das Interpretieren eines Eingabestrings mit der fachlichen Bruttoberechnung.

**Musterlösung:** `parse_amount(text, &amount)` übernimmt das Parsing; `gross_price(net)` die Berechnung; `price(text)` koordiniert beide Phasen.

**Bewertung und Fallstricke:** Das Fehlerverhalten (`-1`) und die Interpretation ungültiger Eingaben sollen erhalten bleiben. `strtod()` erfordert besondere Aufmerksamkeit für `NULL`, Überlauf, Leerzeichen und Sonderwerte; der Beispielcode deckt nicht jeden denkbaren Fall robust ab.

**Nachbesprechung:** Welche Fehler gehören in die Parsing-Phase, welche in die Fachlogik? Ist die Rückgabe `-1` als Fehlerwert eindeutig?

**Quellen im Repository:** [Beschreibung](../../refactoring/split-phase/README.md) · [Before](../../refactoring/split-phase/before/) · [After](../../refactoring/split-phase/after/) · [Gemeinsame Tests](../../refactoring/split-phase/test.c)

## Übergreifende Nachbesprechung

### 1. Refactoring und API-Änderung unterscheiden

Eine interne Umstrukturierung kann bei unveränderter API vollständig verhaltensneutral sein, etwa **Extract Function**. Bei **Introduce Parameter Object**, **Opaque Type**, **Global State to Context** oder **Make Ownership Explicit** ändert sich dagegen die Aufruf- beziehungsweise Lebenszyklusschnittstelle. Die Adapter in den Übungen erleichtern den Vergleich, ersetzen aber nicht die Prüfung realer Aufrufer.

Bei **Replace Error Sentinel** wird die API-Semantik sogar absichtlich verbessert: Ein zuvor mehrdeutiger Rückgabewert wird in Status und Ergebnis aufgeteilt. Das darf nicht als rein mechanisches, verhaltensneutrales Refactoring dargestellt werden.

### 2. Tests als Sicherheitsnetz, nicht als Beweis

Gemeinsame Verhaltenstests sichern ausgewählte Eingaben und Ausgaben ab. Zusätzlich zu prüfen sind insbesondere:

- ungültige Zeiger, Grenzwerte und Fehlerprioritäten;
- Initialisierung und Unabhängigkeit mehrerer Kontexte;
- Speicherbesitz, Freigabe und Ressourcenfehlerpfade;
- die neuen öffentlichen API-Verträge, soweit diese über die gemeinsamen Tests hinausgehen.

### 3. C-spezifische Entwurfsentscheidungen

C90 bietet keine Klassen, aber Module, `struct`-Typen, unvollständige Typen, Funktionszeiger und dateilokale Funktionen. Diese Mittel erlauben Kapselung und klare Verantwortlichkeiten, ohne objektorientierte Sprachmittel vorauszusetzen.

Ein gezieltes `goto cleanup` ist bei der Freigabe mehrerer Ressourcen nicht grundsätzlich ein Anti-Pattern. Ebenso ist eine Dispatch-Tabelle nicht automatisch verständlicher als ein `switch`.

### 4. Abschlussfragen

- Welcher konkrete Code Smell wurde tatsächlich reduziert?
- Welche neue Komplexität oder Abhängigkeit entsteht?
- Wurde die öffentliche API verändert? Falls ja: Sind Aufrufer und Verträge angepasst?
- Welche Testfälle fehlen, um die kritischen Randbedingungen abzudecken?
- Würde die `after`-Variante in einem realen Projekt die Wartbarkeit erhöhen?

**Didaktischer Kern:** Nicht die Anzahl angewandter Refactorings entscheidet über Codequalität, sondern die nachvollziehbare Verbesserung der Struktur bei kontrolliertem Verhalten und expliziten Verträgen.
