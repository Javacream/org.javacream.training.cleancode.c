# Block 05 – Kontrollfluss und Code-Struktur

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/05-kontrollfluss/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Entscheidungspfade in `dirty/main.c`

Die Ausgangsfunktion prüft in verschachtelten `if`-Blöcken zuerst `blocked`, dann `weight > 0`, dann die Versandart und gegebenenfalls `international`. Fehlerfälle werden teils spät über `cost = -1` behandelt. Der Rückgabewert `-1` kennzeichnet ungültige Eingaben.

## 2. Musterlösung anhand von `clean/main.c`

```c
if (blocked || weight <= 0) return -1;
switch (mode) {
    case PICKUP:   return 0;
    case STANDARD: return international ? 20 : 5;
    case EXPRESS:  return international ? 35 : 15;
    default:       return -1;
}
```

Die **Guard Clause** macht die Vorbedingungen sichtbar und beendet ungültige Aufrufe früh. Der `switch` gruppiert die drei diskreten Versandarten. `PICKUP`, `STANDARD` und `EXPRESS` ersetzen numerische Fallunterscheidungen; die Preise bleiben bewusst unverändert.

## 3. Testmatrix / Verhaltensvertrag

| Gewicht | Versandart | International | Gesperrt | Erwartung |
|---:|---|---:|---:|---:|
| 10 | Abholung (0) | 0 | 0 | 0 |
| 10 | Abholung (0) | 1 | 0 | 0 |
| 10 | Standard (1) | 0 | 0 | 5 |
| 10 | Standard (1) | 1 | 0 | 20 |
| 10 | Express (2) | 0 | 0 | 15 |
| 10 | Express (2) | 1 | 0 | 35 |
| 0 | Standard (1) | 0 | 0 | -1 |
| -1 | Express (2) | 0 | 0 | -1 |
| 10 | Standard (1) | 0 | 1 | -1 |
| 10 | Unbekannt (3) | 0 | 0 | -1 |

Die Programme `main()` rufen standardmäßig nur `shipping_cost(10, 2, 0, 0)` auf und geben **15** aus. Die übrigen Fälle sind durch ergänzte Testaufrufe oder einen kleinen Testtreiber zu prüfen; `make test` deckt sie nicht automatisch ab.

## 4. Erfolgskriterien

- Gültige und ungültige Pfade sowie `-1` als Fehlerwert erklärt.
- Guard Clause und `switch` anhand ihrer jeweiligen Aufgabe begründet.
- Die Testmatrix liefert in `dirty` und `clean` identische Werte.
- Geringere Verschachtelung wird nicht mit automatisch geringerer zyklomatischer Komplexität gleichgesetzt.

## 5. Reflexion – Musterantworten

**Warum kann die CCN gleich bleiben?** Guard Clauses und `switch` ordnen Entscheidungen neu, beseitigen aber nicht zwingend Entscheidungsmöglichkeiten. Die Anzahl möglicher Pfade kann ähnlich bleiben, obwohl der Code leichter zu lesen ist.

**Welche Variante ist leichter erweiterbar?** Bei einer zusätzlichen diskreten Versandart ist der `switch` oft übersichtlicher. Bei sehr vielen Varianten kann eine andere Dispatch-Struktur sinnvoll werden; für drei Fälle wäre sie überdimensioniert.

**Welche Grenze hat die Musterlösung?** Die Gewichtsangabe wird nur auf Positivität geprüft; eine gewichtsabhängige Preisstaffel existiert nicht. Eine solche Erweiterung wäre eine neue Fachanforderung, kein Refactoring.
