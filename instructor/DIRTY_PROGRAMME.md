# Trainerpräsentation: Die Ausgangsprogramme (`dirty`)

**Ziel:** Diese Unterlage dient der **einführenden Präsentation vor der jeweiligen Übung**. Sie erklärt die fachliche Aufgabe des Programms, zeigt auffällige Implementierungsentscheidungen und liefert Hinweise auf Code Smells, ohne die spätere `clean`-Lösung vorwegzunehmen.

**Einsatz:** Zu Beginn jedes Blocks zunächst die Ausgangsdatei öffnen, das fachliche Verhalten gemeinsam herleiten, ein bis zwei Auffälligkeiten diskutieren und erst dann die Teilnehmenden selbst untersuchen lassen. Die Hinweise auf Smells sind **Trainerwissen**; sie müssen nicht vollständig vorab verraten werden.

**Abgrenzung:** Betrachtet werden die **acht Programme** in `blocks/*/dirty/`. In Block 08 bilden `main.c`, `logic.c`, `logic.h` und `test.c` eine gemeinsame Anwendung. Die 13 separaten `refactoring/*/before/`-Beispiele gehören nicht zu diesem Dokument.

---

## Block 01 – Grundlagen: Bestellsumme mit Rabatt

**Datei:** [`blocks/01-grundlagen/dirty/main.c`](../blocks/01-grundlagen/dirty/main.c)

### Was macht das Programm?

Es berechnet einen Gesamtbetrag aus einem Einzelpreis und einer Menge. Überschreitet der Betrag 300, wird ein fester Rabatt von 30 abgezogen. Anschließend gibt es die Gesamtsumme aus.

**Konkreter Ablauf:** `p = 120`, `q = 3` → `r = 360` → Bedingung `r > 300` wahr → `r = 330` → Ausgabe `Total: 330`.

### Besonderheiten der Implementierung

- Alle Werte sind fest in `main()` kodiert; es gibt keine Eingaben.
- Der Schwellenwert `300` und der Rabatt `30` sind nicht fachlich benannt.
- Die Bezeichner `p`, `q` und `r` verraten nicht, welche Werte sie repräsentieren.
- Die begleitende [`dirty/doc.md`](../blocks/01-grundlagen/dirty/doc.md) erläutert den Code; die Frage ist, welche Erklärungen durch bessere Namen überflüssig werden.

### Hinweise auf Code Smells

**Unklare Namen**, **Magic Numbers**, fehlende erkennbare fachliche Absicht. Für das aktuelle Beispiel ist `r > 300` wegen der fest kodierten Werte immer wahr; Cppcheck kann dies als konstante Bedingung erkennen. Das ist kein allgemeiner Beweis, dass die Rabattregel überflüssig wäre.

### Präsentationsfragen

„Was bedeuten `p`, `q` und `r`?“ – „Warum werden genau 30 abgezogen?“ – „Ist `doc.md` wirklich nötig, oder erklärt sie nur unleserlichen Code?“

**Didaktischer Fokus:** Verständlichkeit und selbstdokumentierender Code; keine komplexe Umstrukturierung.

---

## Block 02 – Code Smells: Zwei Bestellvarianten

**Datei:** [`blocks/02-code-smells/dirty/main.c`](../blocks/02-code-smells/dirty/main.c)

### Was macht das Programm?

Die Funktion `process()` berechnet **zwei Varianten einer Bestellung**. In beiden Fällen werden Einzelpreis und Menge multipliziert, optional 10 % Premium-Rabatt abgezogen und bei `delivery == 1` eine Liefergebühr von 15 addiert. Variante B verwendet **eine Einheit mehr** als Variante A. Die Ergebnisse werden ausgegeben; `last_total` speichert zuletzt den Wert von B.

**Konkreter Ablauf:** `process(80, 4, 1, 1)`:
- Bestellung A: `80 × 4 = 320`, Rabatt `32`, Lieferung `15` → `Order A: 303`.
- Bestellung B: `80 × 5 = 400`, Rabatt `40`, Lieferung `15` → `Order B: 375`.
- Abschließend `Last: 375`.

### Besonderheiten der Implementierung

- `last_total` ist **globaler veränderlicher Zustand**.
- Berechnung, Rabatt, Liefergebühr, Speicherung und Ausgabe sind in `process()` vermischt.
- Die Berechnung für A und B ist nahezu identisch und wird wiederholt.
- `unused` wird nur über `(void)unused` als verwendet markiert.
- `if (total > 300) total += 0;` hat keine Wirkung.
- `process()` gibt den Betrag von B zurück, obwohl `main()` diesen Rückgabewert ignoriert.

### Hinweise auf Code Smells

**Duplicated Code**, **Global Mutable State**, **Dead/Redundant Code**, **Mixed Responsibilities**, wenig aussagekräftiger Funktionsname. Nicht jeder Smell ist automatisch ein fachlicher Bug; `total += 0` ist hier redundant, aber verändert das Ergebnis nicht.

### Präsentationsfragen

„Warum gibt es zwei fast gleiche Berechnungsblöcke?“ – „Wozu dient `last_total`?“ – „Welche Stelle ist sicher überflüssig, welche erfordert eine Entwurfsentscheidung?“

**Didaktischer Fokus:** Smells erkennen und priorisieren; die umfassende Zerlegung kommt später.

---

## Block 03 – Namen und Datentypen: Versandbereitschaft

**Datei:** [`blocks/03-namen-datentypen/dirty/main.c`](../blocks/03-namen-datentypen/dirty/main.c)

### Was macht das Programm?

Das Programm liest vier Kommandozeilenparameter ein: Versandstatus, Zahlungsstatus, Kennzeichen für eine ungültige Adresse und Sendungsnummer. Es prüft zunächst Anzahl und Wertebereich der Eingaben. Eine Sendung ist nur **bereit**, wenn sie bereits den Status `2` hat, bezahlt ist und die Adresse **nicht** als ungültig markiert wurde.

**Eingaben:** `STATUS(0–2) PAID(0/1) INVALID_ADDRESS(0/1) ID(>=0)`. Statuswerte laut Aufgabenstellung: `0` angelegt, `1` verpackt, `2` versendet.

**Beispiel:** `./app 2 1 0 3` → `Shipment 3: ready`. Bei `./app 1 1 0 3` folgt `Shipment 3: not ready`.

### Besonderheiten der Implementierung

- `s`, `x`, `y`, `z` tragen keine fachliche Bedeutung im Namen.
- Statuswerte `0`, `1`, `2` und die booleschen `0/1`-Werte sind unbenannte Zahlen.
- Die gesamte Validierung steht in einer langen `if`-Bedingung mit mehreren `sscanf`-Aufrufen.
- C90 hat kein standardisiertes `bool` aus `<stdbool.h>`; die booleschen Werte werden mit `int` dargestellt.
- Die Validierung verwendet `sscanf(..., "%d", ...)` und prüft auf eine gelesene Zahl; das ist **keine vollständige Prüfung auf ausschließlich numerische Zeichen**. Das Beispiel zielt aber auf Namen und Typen, nicht auf eine neue Parser-Implementierung.

### Hinweise auf Code Smells

**Cryptic Names**, **Primitive Obsession**, **Magic Numbers**. Die lange Bedingung ist ebenfalls schwer zu lesen, soll in diesem Block jedoch **nicht** primär refaktoriert werden.

### Präsentationsfragen

„Wofür stehen `x` und `y`?“ – „Welche Werte gehören in ein `enum`?“ – „Welche Bedeutung hätte ein sprechender Name für die Bedingung `s == 2 && x == 1 && y == 0`?“

**Didaktischer Fokus:** Namen und Ausdruckskraft, nicht CCN-Reduktion.

---

## Block 04 – Funktionen: Bestellverarbeitung

**Datei:** [`blocks/04-funktionen/dirty/main.c`](../blocks/04-funktionen/dirty/main.c)

### Was macht das Programm?

`process_order()` berechnet eine Bestellsumme, prüft die Menge, gewährt bei Premiumkunden 10 % Rabatt, addiert Versandkosten und gibt die Summe aus. Optional wird der Kundenname angezeigt. Liegt die Endsumme über 500, erscheint zusätzlich `Large order`.

**Konkreter Ablauf:** `process_order(120, 5, "Miller", 1, 1, 10)`: `600 - 60 + 10 = 550`; Ausgabe von `Customer: Miller`, `Total: 550` und `Large order`.

### Besonderheiten der Implementierung

- Eine Funktion übernimmt **Validierung, Berechnung, Rabattregel, Versandkosten und Ausgabe**.
- Sechs Parameter, darunter mehrere unbenannte `int`-Flags, erschweren die Lesbarkeit der Aufrufstelle.
- `print_details` steuert die Ausgabe, nicht die Berechnung.
- Die Menge wird **erst nach** `int total = unit_price * quantity;` validiert. Das ist eine auffällige Reihenfolge, auch wenn für die dokumentierten Eingaben keine sichtbare Abweichung entsteht.
- Die Funktion gibt `void` zurück; Ergebnis und Fehler werden nur über `printf` sichtbar.

### Hinweise auf Code Smells

**Long Parameter List**, **Mixed Responsibilities**, **Side Effects**, **Magic Numbers** (`10`, `500`). Die fachliche Berechnung ist mit Präsentationslogik gekoppelt.

### Präsentationsfragen

„Wie viele Aufgaben erledigt `process_order()`?“ – „Welche Werte gehören zusammen?“ – „Welche Funktion könnte eine Summe berechnen, ohne etwas auszugeben?“

**Didaktischer Fokus:** Fachlich begründete Funktionsgrenzen und Parameterobjekt `Order` als mögliche Alternative.

---

## Block 05 – Kontrollfluss: Versandkosten

**Datei:** [`blocks/05-kontrollfluss/dirty/main.c`](../blocks/05-kontrollfluss/dirty/main.c)

### Was macht das Programm?

`shipping_cost()` berechnet Versandkosten anhand von Gewicht, Versandart, Auslandsversand und Sperrkennzeichen. Bei gesperrter Bestellung, nichtpositivem Gewicht oder unbekannter Versandart liefert die Funktion `-1`.

**Tarife:**

| Versandart | Inland | Ausland |
|---|---:|---:|
| Abholung (`0`) | 0 | 0 |
| Standard (`1`) | 5 | 20 |
| Express (`2`) | 15 | 35 |

**Beispiel:** `shipping_cost(10, 2, 0, 0)` → `15`, also Ausgabe `15`.

### Besonderheiten der Implementierung

- Der Normalfall ist mehrfach in `if`-Blöcke verschachtelt.
- Fehlerfälle werden am Ende der jeweiligen Verzweigung auf `cost = -1` gesetzt, statt früh zurückzugeben.
- Die Versandart wird über eine `if/else if`-Kette statt z. B. über `switch` behandelt.
- Das Gewicht beeinflusst die Höhe der Kosten **nicht**; es wird ausschließlich auf `> 0` geprüft.
- Der Fehlercode `-1` ist ein Sentinel, dessen Bedeutung nur ein Kommentar erläutert.

### Hinweise auf Code Smells

**Deep Nesting**, **Obscured Happy Path**, **Magic Numbers**, **Error Sentinel**. Eine Guard-Clause-Umstellung kann die Verschachtelung verringern, ohne die CCN zu senken.

### Präsentationsfragen

„Wo liegt der eigentliche Normalfall?“ – „Welche Bedingungen könnten sofort `-1` zurückgeben?“ – „Was darf sich bei der Umstellung an Fehlercodes und Tarifwerten nicht ändern?“

**Didaktischer Fokus:** Kontrollfluss und Lesbarkeit, nicht neue Versandtarife.

---

## Block 06 – Metriken: Risikobewertung

**Datei:** [`blocks/06-metriken/dirty/main.c`](../blocks/06-metriken/dirty/main.c)

### Was macht das Programm?

Die Funktion `risk_score()` berechnet aus Alter, Anzahl von Vorfällen, Zahlungsverzug und Verifizierungsstatus einen ganzzahligen Risikowert. Dabei gelten für Personen unter 21 Jahren andere Gewichtungen als für ältere Personen. `category()` ordnet den Score in die Kategorien `0` bis `3` ein.

**Wesentliche Regeln:**
- Unter 21: Grundzuschlag `2`; bei mindestens einem Vorfall weitere `3`; bei gleichzeitigem Verzug weitere `2`; ohne Vorfall, aber mit Verzug `1`.
- Ab 21: mehr als zwei Vorfälle `+3`, ein oder zwei Vorfälle `+1`; Verzug `+2`.
- Nicht verifiziert und zugleich Score `> 2` oder Vorfälle `> 1`: `+2`.
- Kategorien: Score `0` → `0`; `1–3` → `1`; `4–6` → `2`; ab `7` → `3`.

**Konkreter Ablauf:** `risk_score(20, 2, 1, 0)` → `2 + 3 + 2 + 2 = 9`; `category(9)` → `3`. Das Programm gibt `3` aus.

### Besonderheiten der Implementierung

- Altersabhängige Regeln sind verschachtelt; mehrere Bedingungen beeinflussen denselben Score.
- Die Kategoriegrenzen sind als Zahlenwerte im Code eingebettet.
- Die Funktionen `risk_score()` und `category()` sind immerhin getrennt; das Beispiel ist also **nicht in jeder Hinsicht schlechter Code**.
- Unterschiedliche Regeln für verschiedene Altersgruppen machen den Kontrollfluss nichttrivial.
- Der Code verarbeitet keine echten personenbezogenen Daten; er ist ein künstliches Rechenbeispiel, **kein fachlich validiertes Risikomodell**.

### Hinweise auf Code Smells

**Complex Conditional Logic**, **Deep Nesting**, **Magic Numbers**, möglicherweise schwer nachvollziehbare Regelkopplung. Die fachliche Lesbarkeit lässt sich nicht allein aus CCN, NLOC oder der heuristischen Verschachtelung ableiten.

### Präsentationsfragen

„Welche Entscheidungen beeinflussen den Score?“ – „Welche Funktion hat die höchste CCN?“ – „Würde ein niedrigerer CCN-Wert automatisch eine bessere Lösung bedeuten?“

**Didaktischer Fokus:** Metriken anhand konkreten Codes interpretieren und ihre Grenzen erkennen.

---

## Block 07 – Testbarkeit: Bruttopreisberechnung

**Datei:** [`blocks/07-testbarkeit/dirty/main.c`](../blocks/07-testbarkeit/dirty/main.c)

### Was macht das Programm?

`final_price()` berechnet zu einem Nettobetrag eine Steuer anhand des globalen Steuersatzes `current_tax_rate` und gibt den Bruttobetrag sowohl über `printf` als auch als Funktionswert zurück.

**Konkreter Ablauf:** `current_tax_rate = 19`, `final_price(100)` → `100 + 100 × 19 / 100 = 119`; Ausgabe `Calculated: 119`.

### Besonderheiten der Implementierung

- Der Steuersatz ist eine **globale veränderliche Variable**.
- Die Berechnungsfunktion schreibt selbst auf die Standardausgabe.
- Ein isolierter Test muss den globalen Zustand berücksichtigen und erzeugt zusätzlich Konsolenausgabe.
- Ganzzahlarithmetik: Bei anderen Eingaben können Zwischenwerte abgeschnitten werden; Geldbeträge sind im Übungsmodell ganzzahlige Centwerte.
- Die Dirty-Variante hat bewusst **keine eigene automatisierte Testsuite**.

### Hinweise auf Code Smells

**Hidden Dependency**, **Global Mutable State**, **Mixed Calculation and I/O**, **Side Effect**. Die maximale CCN ist bereits niedrig: Ein niedriger Komplexitätswert bedeutet **nicht**, dass eine Funktion gut testbar ist.

### Präsentationsfragen

„Welche Eingaben hat `final_price()` tatsächlich?“ – „Warum ist `current_tax_rate` eine versteckte Abhängigkeit?“ – „Wie könnte ein Test die Berechnung prüfen, ohne Konsolenausgabe auszulösen?“

**Didaktischer Fokus:** Reine Fachlogik und explizite Abhängigkeiten, anschließend Tests und Coverage.

---

## Block 08 – Refactoring: Bestellsumme mit mehreren Regeln

**Dateien:** [`logic.c`](../blocks/08-refactoring/dirty/logic.c), [`logic.h`](../blocks/08-refactoring/dirty/logic.h), [`main.c`](../blocks/08-refactoring/dirty/main.c), [`test.c`](../blocks/08-refactoring/dirty/test.c)

### Was macht das Programm?

Die Funktion `calculate_order_total()` berechnet eine Bestellsumme. Sie akzeptiert Einzelpreis, Menge sowie drei Flags für Premium-Rabatt, Expressversand und Sperre.

**Fachliche Regeln:**
1. Bei gesperrter Bestellung, Menge `<= 0` oder negativem Einzelpreis: Rückgabe `-1`.
2. Sonst Einzelpreis × Menge.
3. Bei Premium: 10 % Rabatt durch Ganzzahldivision.
4. Bei Express: Zuschlag `20`.
5. Wenn die so berechnete Summe **größer als 1000** ist: Abzug `50`.

**Konkreter Ablauf:** `calculate_order_total(100, 12, 1, 1, 0)` → `1200 - 120 + 20 - 50 = 1050`. `main.c` gibt `1050` aus.

### Besonderheiten der Implementierung

- Die **Schnittstelle** in `logic.h` verwendet bereits aussagekräftige Parameternamen; die **Implementierung** in `logic.c` nennt dieselben Parameter nur `p`, `q`, `a`, `b`, `c`.
- Der Normalfall ist in mehreren Bedingungen verschachtelt; der Fehlerwert `-1` wird an zwei Stellen gesetzt.
- Rabatt, Expresszuschlag und Schwellenrabatt sind in einer Funktion kombiniert.
- Die Reihenfolge ist fachlich relevant: Der Schwellenrabatt wird **nach** Premium-Rabatt und Expresszuschlag geprüft.
- `main.c` ist nur ein einfacher Aufrufer. Die Fachlogik liegt bereits in einem separaten Modul.
- `test.c` enthält neun Charakterisierungstests, unter anderem für gesperrte Bestellungen, ungültige Werte, Premium, Express und die Schwelle bei 1000.

### Hinweise auf Code Smells

**Cryptic Names**, **Deep Nesting**, **Magic Numbers**, **Mixed Responsibilities**, **Error Sentinel**. Die Modultrennung und die vorhandenen Tests sind hingegen positive Eigenschaften der Ausgangsversion.

### Präsentationsfragen

„Welche Regeln müssen exakt erhalten bleiben?“ – „Warum ist `1000` ein besonders wichtiger Testwert?“ – „Welche zwei Refactorings würden wir in welcher Reihenfolge durchführen?“ – „Was prüfen wir nach jedem Schritt?“

### Testvorführung

Im Verzeichnis `blocks/08-refactoring/dirty/`:

```sh
make check
```

Die vorhandenen Tests prüfen insbesondere:
- Sperre, Menge null und negativen Einzelpreis → `-1`
- Normale Bestellung `500`, Premium `450`, Express `520`
- Kombination aus Premium und Express → `1050`
- Schwelle genau `1000` → kein zusätzlicher Rabatt
- Summe oberhalb der Schwelle → Rabatt `50`

**Didaktischer Fokus:** Erst Tests, dann zwei **kleine, getrennte** Refactoring-Schritte und nach jedem Schritt erneut testen. Nicht alle Smells in einem großen Umbau beseitigen.

---

## Abschließende Trainerhinweise

**Präsentationsmuster pro Block:** 1. fachliches Ziel in einem Satz erläutern; 2. konkrete Eingaben und erwartete Ausgabe gemeinsam berechnen; 3. Code von außen nach innen lesen; 4. auffällige Stellen markieren, ohne die Lösung vorzugeben; 5. Übung starten; 6. erst danach `clean` vergleichen.

**Wichtige Differenzierung:** Nicht jede Auffälligkeit ist ein Bug. Einige Ausgangsprogramme besitzen bereits sinnvolle Eigenschaften, etwa getrennte Funktionen in Block 06 oder Charakterisierungstests in Block 08. Ein Code Smell ist ein Anlass zur Prüfung, keine automatische Änderungsanweisung.

**Zeiteinsatz im Zweitageskurs:** Diese Unterlage ist ein **Sprech- und Präsentationsleitfaden** und keine zusätzliche Unterrichtseinheit. Die Vorstellung jedes Ausgangsprogramms erfolgt innerhalb der Zeitbudgets des [kompakten Trainerleitfadens](TRAINERLEITFADEN_2_TAGE.md).
