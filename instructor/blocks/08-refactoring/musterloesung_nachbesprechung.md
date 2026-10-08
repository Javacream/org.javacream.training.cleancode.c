# Block 08 – Refactoring und kontinuierliche Verbesserung

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/08-refactoring/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Ausgangslage und Verhaltensvertrag

In `dirty/logic.c` berechnet `calculate_order_total(int p, int q, int a, int b, int c)` den Bestellbetrag. Die fünf wenig sprechenden Parameter stehen für Einzelpreis, Menge, Premium, Express und Sperre. Die Funktion verwendet verschachtelte Bedingungen, die Variable `x` und Magic Numbers.

Fachregeln in der **vorgegebenen Reihenfolge**:

1. Bei `blocked != 0`, `quantity <= 0` oder `unit_price < 0` Ergebnis **-1**.
2. Grundbetrag = Einzelpreis × Menge.
3. Premium: 10 % des aktuellen Betrags abziehen (Integerdivision).
4. Express: 20 addieren.
5. Falls der dann aktuelle Betrag **größer als 1000** ist: 50 abziehen.

Die Reihenfolge ist fachlich relevant; ein Umordnen kann andere Ergebnisse erzeugen.

## 2. Refactoring-Plan und Musterlösung

| Schritt | Änderung | Begründung | Test danach |
|---|---|---|---|
| 0 | Ausgangsversion unverändert testen | Verhalten charakterisieren | `make check` in `dirty/` |
| 1 | Parameter und Variable umbenennen: `p` → `unit_price`, `q` → `quantity`, `x` → `total` usw. | Fachliche Absicht sichtbar machen | `make check` |
| 2 | Fehlerpfade als Guard Clause ausdrücken | Verschachtelung verringern | `make check` |
| 3 | `EXPRESS_FEE`, `LARGE_ORDER_THRESHOLD`, `LARGE_ORDER_DISCOUNT` benennen | Magic Numbers vermeiden | `make check` |
| 4 | `apply_premium_discount`, `apply_express_fee`, `apply_large_order_discount` extrahieren | Einzelne Berechnungsregeln isolieren | `make check` |

Die Referenz in `clean/logic.c` realisiert diese Struktur mit `static`-Hilfsfunktionen. **Wichtig:** Die in der README geforderten mindestens zwei getrennten Änderungen können auch eine Teilmenge dieses Plans sein. Es ist nicht notwendig, alle Schritte umzusetzen.

## 3. Charakterisierungstests

`dirty/test.c` und `clean/test.c` enthalten dieselben neun fachlichen Prüfungen:

| Test | Erwartung |
|---|---:|
| Gesperrte Bestellung | -1 |
| Menge 0 | -1 |
| Negativer Einzelpreis | -1 |
| Regulär: 100 × 5 | 500 |
| Premium: 100 × 5 | 450 |
| Express: 100 × 5 | 520 |
| Kombiniert: 100 × 12, Premium und Express | 1050 |
| Schwelle exakt: 100 × 10 | 1000 |
| Oberhalb Schwelle: 100 × 11 | 1050 |

Der kombinierte Fall ergibt 1200 − 120 + 20 − 50 = **1050**. Bei exakt 1000 wird kein 50er-Rabatt gewährt, weil die Bedingung `> 1000` und nicht `>= 1000` lautet.

In `dirty/` vor jeder Änderung und nach jedem Schritt:

```sh
make check
```

Anschließend dasselbe in `clean/` ausführen und die Implementierungen vergleichen. Das Vorhandensein der Tests allein ist kein Nachweis, dass sie in dieser Nachbesprechung ausgeführt wurden.

## 4. Erfolgskriterien

- Die wesentlichen Code Smells und ihr Einfluss auf die Änderbarkeit sind benannt.
- Ein Refactoring-Plan mit mindestens zwei **getrennten** Schritten und Reihenfolge liegt vor.
- Vor und nach **jedem** Schritt laufen die vorhandenen Charakterisierungstests erfolgreich.
- Die Teilnehmenden erläutern die Verbesserung anhand von Namen, Verantwortlichkeiten und Kontrollfluss, nicht bloß anhand der Zeilenzahl.
- Kein neues Fachverhalten wird stillschweigend eingeführt.

## 5. Reflexion – Musterantworten

**Was sollte bewusst nicht geändert werden?** Die Rabattprozentsätze, die Reihenfolge der Zuschläge, die Grenzwertregel `> 1000` und die Fehlersemantik `-1`. Auch eine Umstellung auf Fließkomma wäre keine reine Strukturverbesserung.

**Warum kleine Schritte?** Bei einem fehlgeschlagenen Test lässt sich die Ursache auf die jüngste Änderung eingrenzen. Kleine Commits und häufige Tests machen Refactoring überprüfbar.

**Welche Risiken bleiben trotz grüner Tests?** Ungetestete Kombinationen, Integer-Überlauf bei großen Preisen oder Mengen sowie mögliche Missverständnisse der Fachanforderungen. Neun Tests sind eine nützliche Charakterisierung, aber kein Vollständigkeitsbeweis.

**Sind die Hilfsfunktionen zwingend?** Nein. Eine andere Lösung ist zulässig, wenn sie verständlich, C90-konform und verhaltenserhaltend ist.
