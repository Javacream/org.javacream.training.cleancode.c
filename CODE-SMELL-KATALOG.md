# Code-Smell-Katalog – Clean Code mit C90

> Schulungsbegleitende Referenz für die Blöcke 02–08. Ein **Code Smell** ist ein Hinweis auf ein mögliches Wartbarkeits- oder Strukturproblem, **kein automatischer Nachweis eines Bugs**. Die hier genannten Kategorien kombinieren klassische Begriffe aus der Refactoring-Literatur mit verbreiteten, praxisnahen Qualitätsindikatoren. Sie sind keine normative oder vollständige Liste.

## Verwendung in der Schulung

1. **Fundstelle** im Code angeben und das beobachtete Problem beschreiben.
2. **Auswirkung** auf Lesbarkeit, Wartbarkeit oder Testbarkeit begründen.
3. **Smell oder Bug?** Fachliches Sollverhalten und tatsächliches Verhalten unterscheiden.
4. **Priorisieren:** Auswirkung, Änderungsrisiko und Aufwand abwägen.
5. **Refactoring vorschlagen:** Verhaltensvertrag und Tests vor einer Änderung klären.

Die ergänzende [Code-Smell-Refactoring-Matrix](CODE-SMELL-REFACTORING-MATRIX.md) enthält weitere C-spezifische Techniken und Einschränkungen.

## Übersicht

| Code Smell / Beobachtung | Typisches Problem | Seminarbezug |
|---|---|---|
| [Unklare Namen (Mysterious Name)](#smell-01) | Namen wie `x`, `s` oder `process` verschleiern die Absicht. | [Block 03](blocks/03-namen-datentypen/dirty/main.c) |
| [Magische Zahlen (Magic Numbers)](#smell-02) | Fachliche Werte sind als nackte Literale im Code verteilt. | [Block 08](blocks/08-refactoring/dirty/logic.c) |
| [Unnötiger Code (Dead Code)](#smell-03) | Anweisungen oder Variablen haben keinen relevanten Effekt. | [Block 02](blocks/02-code-smells/dirty/main.c) |
| [Doppelter Code (Duplicated Code)](#smell-04) | Eine Regel ist an mehreren Stellen implementiert. | [Block 02](blocks/02-code-smells/dirty/main.c) |
| [Lange oder überladene Funktion (Long Function)](#smell-05) | Eine Funktion umfasst mehrere Schritte und Verantwortlichkeiten. | [Block 04](blocks/04-funktionen/dirty/main.c) |
| [Lange Parameterliste (Long Parameter List)](#smell-06) | Viele Positionsparameter erschweren korrekte Aufrufe. | [Block 04](blocks/04-funktionen/dirty/main.c) |
| [Datenklumpen (Data Clumps)](#smell-07) | Dieselbe Gruppe fachlich zusammengehöriger Werte wandert gemeinsam durch Funktionen. | [Block 04](blocks/04-funktionen/clean/main.c) |
| [Global veränderlicher Zustand (Global Data)](#smell-08) | Funktionen lesen oder schreiben globale Variablen. | [Block 02](blocks/02-code-smells/dirty/main.c), [Block 07](blocks/07-testbarkeit/dirty/main.c) |
| [Veränderliche Daten (Mutable Data)](#smell-09) | Änderungen an gemeinsam genutzten Daten sind schwer nachzuvollziehen. | [Block 07](blocks/07-testbarkeit/dirty/main.c) |
| [Tiefe Verschachtelung (Deep Nesting)](#smell-10) | Der Normalfall liegt hinter mehreren Ebenen von Bedingungen. | [Block 05](blocks/05-kontrollfluss/dirty/main.c) |
| [Komplizierte Bedingungen (Complex Conditional)](#smell-11) | Zusammengesetzte Bedingungen erfordern hohe mentale Last. | [Block 06](blocks/06-metriken/dirty/main.c) |
| [Vermischte Phasen / Verantwortlichkeiten (Mixed Concerns)](#smell-12) | Fachberechnung, Ausgabe oder Einlesen sind eng gekoppelt. | [Block 07](blocks/07-testbarkeit/dirty/main.c) |
| [Unterschiedliche Änderungsgründe (Divergent Change)](#smell-13) | Eine Komponente muss für mehrere unabhängige Fachthemen geändert werden. | [Block 04](blocks/04-funktionen/dirty/main.c) |
| [Verstreute Änderungen (Shotgun Surgery)](#smell-14) | Eine einzelne fachliche Änderung verlangt Anpassungen an vielen Stellen. | [Block 02](blocks/02-code-smells/dirty/main.c) |
| [Kommentar als Ersatz für Klarheit (Comments)](#smell-15) | Kommentare erklären schwer verständlichen Code statt fachliche Entscheidungen. | [Block 03](blocks/03-namen-datentypen/dirty/main.c) |
| [Schwer testbarer Code (Testability Smell)](#smell-16) | Abhängigkeiten und Nebenwirkungen verhindern einfache Unit-Tests. | [Block 07](blocks/07-testbarkeit/dirty/main.c) |

## Katalogeinträge

<a id="smell-01"></a>

### 1. Unklare Namen (Mysterious Name)

**Erkennung:** Namen wie `x`, `s` oder `process` verschleiern die Absicht.

**C90-Beispiel:** `int s; if (s == 2) ...`

**Mögliche Auswirkung:** Falsche Annahmen beim Lesen und Ändern.

**Mögliche Gegenmaßnahme:** Rename Variable / Rename Function; fachlich benannte Zustände.

**Beispiel im Kurs:** [Block 03](blocks/03-namen-datentypen/dirty/main.c).

<a id="smell-02"></a>

### 2. Magische Zahlen (Magic Numbers)

**Erkennung:** Fachliche Werte sind als nackte Literale im Code verteilt.

**C90-Beispiel:** `if (total > 1000) total -= 50;`

**Mögliche Auswirkung:** Regeländerungen werden fehleranfällig.

**Mögliche Gegenmaßnahme:** Replace Magic Number with Symbolic Constant; Wertebereich und Bedeutung prüfen.

**Beispiel im Kurs:** [Block 08](blocks/08-refactoring/dirty/logic.c).

<a id="smell-03"></a>

### 3. Unnötiger Code (Dead Code)

**Erkennung:** Anweisungen oder Variablen haben keinen relevanten Effekt.

**C90-Beispiel:** `if (total > 300) total += 0;`

**Mögliche Auswirkung:** Lenkt ab und suggeriert eine nicht vorhandene Regel.

**Mögliche Gegenmaßnahme:** Remove Dead Code nach Prüfung möglicher Seiteneffekte.

**Beispiel im Kurs:** [Block 02](blocks/02-code-smells/dirty/main.c).

<a id="smell-04"></a>

### 4. Doppelter Code (Duplicated Code)

**Erkennung:** Eine Regel ist an mehreren Stellen implementiert.

**C90-Beispiel:** `if (premium) total -= total / 10;` an zwei Stellen.

**Mögliche Auswirkung:** Änderungen können inkonsistent werden.

**Mögliche Gegenmaßnahme:** Extract Function; gemeinsame Logik nur bei tatsächlich gleichem Fachkonzept.

**Beispiel im Kurs:** [Block 02](blocks/02-code-smells/dirty/main.c).

<a id="smell-05"></a>

### 5. Lange oder überladene Funktion (Long Function)

**Erkennung:** Eine Funktion umfasst mehrere Schritte und Verantwortlichkeiten.

**C90-Beispiel:** `process_order` validiert, berechnet und druckt.

**Mögliche Auswirkung:** Erhöht kognitive Last und erschwert Tests.

**Mögliche Gegenmaßnahme:** Extract Function nach fachlichen Aufgaben.

**Beispiel im Kurs:** [Block 04](blocks/04-funktionen/dirty/main.c).

<a id="smell-06"></a>

### 6. Lange Parameterliste (Long Parameter List)

**Erkennung:** Viele Positionsparameter erschweren korrekte Aufrufe.

**C90-Beispiel:** `process_order(unit_price, quantity, customer, premium, print_details, shipping_fee)`

**Mögliche Auswirkung:** Verwechslungen und schlecht erkennbare Zusammenhänge.

**Mögliche Gegenmaßnahme:** Introduce Parameter Object, falls die Daten zusammengehören.

**Beispiel im Kurs:** [Block 04](blocks/04-funktionen/dirty/main.c).

<a id="smell-07"></a>

### 7. Datenklumpen (Data Clumps)

**Erkennung:** Dieselbe Gruppe fachlich zusammengehöriger Werte wandert gemeinsam durch Funktionen.

**C90-Beispiel:** `unit_price`, `quantity`, `premium`, `shipping_fee`

**Mögliche Auswirkung:** Wiederholung und unklare Schnittstellen.

**Mögliche Gegenmaßnahme:** Introduce Parameter Object / passende `struct`.

**Beispiel im Kurs:** [Block 04](blocks/04-funktionen/clean/main.c).

<a id="smell-08"></a>

### 8. Global veränderlicher Zustand (Global Data)

**Erkennung:** Funktionen lesen oder schreiben globale Variablen.

**C90-Beispiel:** `int last_total = 0;`

**Mögliche Auswirkung:** Verdeckte Abhängigkeiten, erschwerte Tests und Wiederverwendung.

**Mögliche Gegenmaßnahme:** Encapsulate Variable; Zustand ggf. explizit als Kontext übergeben.

**Beispiel im Kurs:** [Block 02](blocks/02-code-smells/dirty/main.c), [Block 07](blocks/07-testbarkeit/dirty/main.c).

<a id="smell-09"></a>

### 9. Veränderliche Daten (Mutable Data)

**Erkennung:** Änderungen an gemeinsam genutzten Daten sind schwer nachzuvollziehen.

**C90-Beispiel:** `current_tax_rate` als globaler Parameter.

**Mögliche Auswirkung:** Reihenfolgeabhängigkeit und unvorhersehbare Auswirkungen.

**Mögliche Gegenmaßnahme:** Zustand begrenzen, Eingaben explizit machen, unveränderliche Parameter bevorzugen.

**Beispiel im Kurs:** [Block 07](blocks/07-testbarkeit/dirty/main.c).

<a id="smell-10"></a>

### 10. Tiefe Verschachtelung (Deep Nesting)

**Erkennung:** Der Normalfall liegt hinter mehreren Ebenen von Bedingungen.

**C90-Beispiel:** `if (!blocked) { if (weight > 0) { ... } }`

**Mögliche Auswirkung:** Fehlerpfade und fachliche Regeln sind schwer zu verfolgen.

**Mögliche Gegenmaßnahme:** Guard Clauses und geeignete Fallunterscheidung; Fehlercodes erhalten.

**Beispiel im Kurs:** [Block 05](blocks/05-kontrollfluss/dirty/main.c).

<a id="smell-11"></a>

### 11. Komplizierte Bedingungen (Complex Conditional)

**Erkennung:** Zusammengesetzte Bedingungen erfordern hohe mentale Last.

**C90-Beispiel:** `!verified && (score > 2 || incidents > 1)`

**Mögliche Auswirkung:** Falsche Änderungen und schwer überprüfbare Grenzfälle.

**Mögliche Gegenmaßnahme:** Extract Function / benannte Prädikate; Kurzschlussverhalten beachten.

**Beispiel im Kurs:** [Block 06](blocks/06-metriken/dirty/main.c).

<a id="smell-12"></a>

### 12. Vermischte Phasen / Verantwortlichkeiten (Mixed Concerns)

**Erkennung:** Fachberechnung, Ausgabe oder Einlesen sind eng gekoppelt.

**C90-Beispiel:** `final_price` berechnet und ruft `printf` auf.

**Mögliche Auswirkung:** Schlechte isolierte Testbarkeit und unnötige Seiteneffekte.

**Mögliche Gegenmaßnahme:** Split Phase, Extract Function, Berechnung von I/O trennen.

**Beispiel im Kurs:** [Block 07](blocks/07-testbarkeit/dirty/main.c).

<a id="smell-13"></a>

### 13. Unterschiedliche Änderungsgründe (Divergent Change)

**Erkennung:** Eine Komponente muss für mehrere unabhängige Fachthemen geändert werden.

**C90-Beispiel:** Bestellberechnung und Belegdruck in einer Funktion.

**Mögliche Auswirkung:** Unabhängige Anforderungen beeinflussen sich gegenseitig.

**Mögliche Gegenmaßnahme:** Extract Function / Verantwortlichkeiten trennen.

**Beispiel im Kurs:** [Block 04](blocks/04-funktionen/dirty/main.c).

<a id="smell-14"></a>

### 14. Verstreute Änderungen (Shotgun Surgery)

**Erkennung:** Eine einzelne fachliche Änderung verlangt Anpassungen an vielen Stellen.

**C90-Beispiel:** Doppelte Rabattregel müsste an mehreren Stellen geändert werden.

**Mögliche Auswirkung:** Änderungen werden leicht übersehen.

**Mögliche Gegenmaßnahme:** Zusammengehörige Regeln an einer Stelle bündeln.

**Beispiel im Kurs:** [Block 02](blocks/02-code-smells/dirty/main.c).

<a id="smell-15"></a>

### 15. Kommentar als Ersatz für Klarheit (Comments)

**Erkennung:** Kommentare erklären schwer verständlichen Code statt fachliche Entscheidungen.

**C90-Beispiel:** `/* 0, 1, 2 */` statt benannter Versandstatus.

**Mögliche Auswirkung:** Kommentar und Code können auseinanderlaufen.

**Mögliche Gegenmaßnahme:** Sprechende Namen und `enum`; Kommentare für Gründe und Verträge.

**Beispiel im Kurs:** [Block 03](blocks/03-namen-datentypen/dirty/main.c).

<a id="smell-16"></a>

### 16. Schwer testbarer Code (Testability Smell)

**Erkennung:** Abhängigkeiten und Nebenwirkungen verhindern einfache Unit-Tests.

**C90-Beispiel:** `final_price` verwendet globalen Steuersatz und schreibt auf stdout.

**Mögliche Auswirkung:** Tests benötigen Zustands- und Ausgabekontrolle.

**Mögliche Gegenmaßnahme:** Pure Function, explizite Parameter, I/O isolieren.

**Beispiel im Kurs:** [Block 07](blocks/07-testbarkeit/dirty/main.c).

## Bewertung und Grenzen

- **Nicht jeder Smell verlangt sofortiges Refactoring.** In Block 02 bleiben Duplikation und globaler Zustand bewusst bestehen; nur wirkungsloser Code wird entfernt.
- **Nicht jede kürzere Implementierung ist besser.** Block 06 zeigt, dass kompakte ternäre Ausdrücke trotz günstiger Kennzahlen schlechter lesbar sein können.
- **Strukturelle Änderung und Fachänderung trennen.** Neue Validierungsregeln, geänderte Rabattgrenzen oder neue Fehlercodes verändern das Verhalten und erfordern eigene Anforderungen und Tests.
- **Metriken sind Hinweise, keine Qualitätsnoten.** CCN, NLOC und heuristische Verschachtelung ersetzen weder Review noch Charakterisierungstests.
- **C90 beachten.** Für Wahrheitswerte wird `int` verwendet; `enum` und `struct` sind verfügbar. `<stdbool.h>` gehört nicht zu C90.

## Nachbesprechung – Leitfragen

1. Welche konkrete Fundstelle begründet den Verdacht?
2. Ist ein falsches Ergebnis nachgewiesen oder lediglich eine künftige Änderungsgefahr?
3. Welches Refactoring passt, und was könnte dabei unbeabsichtigt geändert werden?
4. Welche bestehenden oder zusätzlichen Tests sichern das beobachtbare Verhalten?
5. Wann ist es vernünftig, einen Smell bewusst zu belassen?

## Weiterführende Quellen

- Martin Fowler: *Refactoring: Improving the Design of Existing Code*, 2. Auflage (2018); [Refactoring Catalog](https://refactoring.com/catalog/).
- [Refactoring.Guru – Code Smells](https://refactoring.guru/refactoring/smells).
- Robert C. Martin: *Clean Code* (2008). Die Bezeichnungen dieses Katalogs folgen nicht ausschließlich einer einzelnen Quelle.
