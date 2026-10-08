# Block 07 – Testbarer Code und Clean Tests

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/07-testbarkeit/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Diagnose von `dirty/main.c`

Die Funktion `final_price(int net)` liest die veränderliche globale Variable `current_tax_rate = 19`, berechnet den Bruttobetrag und gibt ihn direkt mit `printf` aus. Zwei Testbarkeitshindernisse sind damit unmittelbar sichtbar:

1. **Verdeckte Eingabe:** Der Steuersatz wird nicht als Parameter übergeben; Testergebnisse hängen von globalem Zustand ab.
2. **Vermischung von Fachlogik und I/O:** Eine Berechnung verursacht eine Konsolenausgabe. Isolierte Tests müssen diese Nebenwirkung berücksichtigen.

Der ursprüngliche Aufruf `final_price(100)` gibt `Calculated: 119` aus.

## 2. Musterlösung anhand von `clean/`

`logic.c` enthält eine reine Berechnungsfunktion:

```c
int calculate_gross_price(int net_cents, int tax_percent)
{
    return net_cents + net_cents * tax_percent / 100;
}
```

Der Steuersatz ist jetzt eine explizite Eingabe; die Ausgabe erfolgt in `main.c`. Das Modul `logic.h` macht die Schnittstelle verfügbar, `test.c` testet sie ohne Konsolenausgabe der Berechnungsfunktion. Die Integerarithmetik rundet durch Abschneiden in Richtung null; für positive Werte entspricht dies dem Abrunden.

## 3. Vorhandene Tests und zusätzlicher Testfall

In `clean/`:

```sh
make check
make coverage
```

Die vorhandenen Tests prüfen unter anderem 100 Cent bei 19 % → 119, 0 % → 100, 101 Cent bei 1 % → 102, 1 Cent bei 19 % → 1 sowie negative und ungewöhnliche Steuersätze als **Charakterisierung des bisherigen Verhaltens**.

**Zusätzlicher Testfall (Vorschlag):** 99 Cent netto bei 19 % Steuer ergeben `99 + 99 * 19 / 100 = 117` Cent. Ergänzung in `test.c`:

```c
failures += assert_equal("99 cents rounding", 117,
                         calculate_gross_price(99, 19));
```

Dieser Test prüft die Rundung an einer weiteren Grenze. Die bestehenden Tests müssen weiterhin erfolgreich bleiben.

## 4. Wichtiger Widerspruch in der Referenz

In `clean/logic.h` steht der Kommentar „Preise in ganzen Cent; negative Eingaben liefern -1.“ Das ist **nicht die implementierte allgemeine Regel**: `calculate_gross_price(100, -1)` ergibt 99 und `calculate_gross_price(-1, 19)` ergibt zufällig -1 durch Integerarithmetik, nicht durch eine Validierungsentscheidung. Die Tests dokumentieren ausdrücklich die unveränderte Behandlung negativer Werte. **Didaktische Konsequenz:** Der Kommentar sollte fachlich korrigiert werden; eine neue Ablehnung negativer Eingaben wäre eine Verhaltensänderung und gehört nicht stillschweigend zum Refactoring.

## 5. Erfolgskriterien

- Globale Abhängigkeit und I/O-Kopplung mit Fundstellen benannt.
- Berechnung und Ausgabe anhand der zwei Module erklärt.
- `make check` und `make coverage` durchgeführt; ein zusätzlicher Test mit erwarteter Zahl formuliert und erfolgreich ausgeführt.
- Coverage als Ausführungsmaß verstanden; kein Schluss von hoher Coverage auf vollständige Fehlerfreiheit.
- Keine neuen Validierungsregeln eingeführt.

## 6. Reflexion – Musterantworten

**Welche Grenzwerte sind besonders wichtig?** Null, ein Cent, Rundungsschwellen, 0 % und 100 % Steuer sowie bewusst definierte ungewöhnliche Eingaben.

**Was sagt eine hohe Coverage aus?** Dass viele Zeilen oder Zweige ausgeführt wurden. Sie zeigt nicht, ob die Assertions fachlich richtig sind oder Grenzfälle fehlen.

**Wie geht man mit Integer-Überlauf um?** Zunächst Anforderungen und zulässige Wertebereiche festlegen. Dann beispielsweise vor der Multiplikation Grenzen prüfen oder einen geeigneten größeren Typ wählen. Das ist eine eigene fachliche beziehungsweise technische Änderung mit eigenen Tests, kein rein verhaltenserhaltendes Refactoring.

**Warum keine Validierung nachrüsten?** Das würde das Verhalten für bisher akzeptierte Werte ändern und damit den Verhaltensvertrag verletzen.
