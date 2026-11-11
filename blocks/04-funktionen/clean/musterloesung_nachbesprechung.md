# Block 04 – Funktionen und Verantwortlichkeiten

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/04-funktionen/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Ausgangscode: Verantwortlichkeiten

In `dirty/main.c` übernimmt `process_order` mehrere Aufgaben zugleich:

1. **Validierung:** `quantity <= 0` führt zur Meldung `Invalid quantity` und zum Abbruch.
2. **Berechnung:** `unit_price * quantity`, gegebenenfalls 10 % Premiumrabatt, anschließend `shipping_fee`.
3. **Ausgabe:** Optionaler Kundenname, Gesamtbetrag und gegebenenfalls `Large order` bei `total > 500`.

Die Funktion besitzt sechs Parameter. Das erschwert die Zuordnung zusammengehöriger Bestelldaten.

## 2. Musterlösung anhand von `clean/main.c`

| Funktion / Typ | Verantwortung | Vertrag |
|---|---|---|
| `Order` | Bündelt Kundenname, Preis, Menge, Premium, Detailausgabe und Versandkosten | Zusammengehöriger Bestelldatensatz |
| `is_valid_order(const Order *)` | Prüft die bisherige Mengenbedingung | Wahr bei `quantity > 0` |
| `calculate_total(const Order *)` | Berechnet Gesamtbetrag ohne Ausgabe | `unit_price * quantity`, Rabatt, Versand |
| `print_receipt(const Order *, int)` | Erzeugt die fachlich definierte Ausgabe | Respektiert `print_details` |
| `process_order(const Order *)` | Koordiniert Prüfung, Berechnung und Ausgabe | Bricht bei ungültiger Menge ab |

Die Funktionen sind `static`, weil sie nur innerhalb der Übersetzungseinheit benötigt werden. `const Order *` dokumentiert, dass der Datensatz nicht verändert werden soll. Die Zerlegung ist nicht allein wegen kürzerer Funktionen sinnvoll, sondern wegen **getrennter Verantwortlichkeiten**.

## 3. Verhaltensvertrag

Für `Order { "Miller", 120, 5, 1, 1, 10 }` gilt: Grundpreis 600, Premiumrabatt 60, Versand 10, Gesamt **550**.

Bei `print_details = 1`:

```text
Customer: Miller
Total: 550
Large order
```

Bei `print_details = 0`:

```text
Total: 550
Large order
```

Bei `quantity <= 0` ist ausschließlich `Invalid quantity` auszugeben. **Prüfhinweis:** Das bereitgestellte `main()` verwendet nur `print_details = 1`. Für den zweiten Zustand muss der Wert im Beispiel vorübergehend geändert oder ein eigener Test ergänzt werden. Das vorhandene `make test` ist kein automatischer Test beider Fälle.

## 4. Erfolgskriterien

- Drei Verantwortlichkeiten mit Codebezug korrekt identifiziert.
- `Order` und die Funktionsgrenzen anhand von Ein- und Ausgaben begründet.
- Beide Detailausgabe-Zustände sowie ungültige Menge geprüft.
- Berechnungsreihenfolge und Grenzwert `total > 500` beibehalten.
- Keine neuen fachlichen Validierungen eingeführt.

## 5. Reflexion – Musterantworten

**Wann ist eine neue Funktion sinnvoll?** Wenn sie eine fachlich verständliche Aufgabe mit klarem Vertrag isoliert, beispielsweise `calculate_total`.

**Wann ist eine Zerlegung schlechter?** Wenn viele triviale Einzeiler nur zusätzliche Sprünge erzeugen und keine eigenständige Verantwortung ausdrücken.

**Warum `Order` statt sechs Parameter?** Die Werte bilden gemeinsam einen fachlichen Datensatz; die Aufrufstelle wird weniger fehleranfällig. Ein Parameterobjekt sollte jedoch nicht beliebige, unzusammenhängende Werte bündeln.

**Was bleibt verbesserungsfähig?** Die Rabatt- und Schwellenwerte sind noch nicht benannt. Das ist für diesen Block keine zwingende Änderung.
