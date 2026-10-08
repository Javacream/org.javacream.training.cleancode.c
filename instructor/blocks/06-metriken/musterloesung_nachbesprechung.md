# Block 06 – Metriken und statische Codeanalyse

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/06-metriken/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Messung reproduzieren

Im Projektwurzelverzeichnis:

```sh
python3 analyze.py --block 06 --output blocks/06-metriken/quality-report-block06.md
```

Im Verzeichnis `blocks/06-metriken/clean`:

```sh
make metrics
make compare
```

Der Bericht muss mit dem **aktuellen** Skript und Werkzeugstand erstellt werden. Zahlenwerte werden hier bewusst nicht als unveränderliche Sollwerte angegeben, da Werkzeugversionen und die konkrete Erhebungsmethode Unterschiede bewirken können. **Es wurde für diese Musterlösung kein neuer Qualitätsbericht ausgeführt.**

## 2. Quellcodeanalyse

**`dirty/main.c`:** `risk_score(age, incidents, overdue, verified)` enthält eine verschachtelte Altersentscheidung, eine abgestufte Vorfallbewertung, die Berücksichtigung überfälliger Vorgänge und einen zusätzlichen Zuschlag bei fehlender Verifikation. Die Bedingung `!verified && (score > 2 || incidents > 1)` zeigt, warum auch zusammengesetzte Bedingungen die Komplexitätsbewertung beeinflussen können.

**`clean/main.c`:** `incident_score` berechnet den Grundwert; `risk_score` ergänzt nur den Verifikationszuschlag. Die Gesamtlogik ist verteilt, weshalb die **maximale CCN je Funktion** sinken kann, ohne dass alle Entscheidungen des Programms verschwinden. Die verschachtelten ternären Operatoren in `incident_score` können trotz kompakter Form schwer lesbar sein.

**`clean/alternative.c`:** Die Alternative nutzt explizite `if`-Zweige und eine eigene Funktion `verification_penalty`. Sie kann länger sein, aber die fachlichen Regeln klarer sichtbar machen. Ob sie besser ist, muss anhand des Codes und der Messwerte diskutiert werden.

**`category(score)`:** Dieselbe Staffelung gilt in allen Varianten: 0 bei Score ≤ 0, 1 bei 1–3, 2 bei 4–6, 3 ab 7.

## 3. Beispielrechnung

Für `risk_score(20, 2, 1, 0)`: Alter unter 21 → 2; Vorfälle vorhanden → +3; überfällig → +2; nicht verifiziert und Score > 2 → +2. Ergebnis: **Score 9, Kategorie 3**. `main()` gibt in den Varianten `3` aus.

## 4. Vergleichstest und Grenzen

`make compare` kompiliert `test_comparison.c` und vergleicht `clean/main.c` mit `clean/alternative.c` über 8 Alterswerte (18–25), 6 Vorfallzahlen (0–5), 2 Überfälligkeits- und 2 Verifikationswerte: **192 Kombinationen**. Erwartete Meldung:

```text
PASS: both implementations agree
```

**Wichtig:** Dieser Test vergleicht die beiden Clean-Implementierungen, **nicht** automatisch `dirty` gegen `clean`. Er belegt Gleichheit nur für die geprüften Kombinationen, nicht für alle möglichen Integerwerte.

## 5. Erfolgskriterien

- Ein reproduzierbarer Bericht wurde erzeugt und die Werkzeugversionen sind nachvollziehbar.
- Die höchste gemessene CCN wird einer konkreten Funktion zugeordnet und anhand ihrer Entscheidungen erläutert.
- CCN, NLOC, Parameterzahl und heuristische Verschachtelung werden getrennt interpretiert.
- Mindestens zwei Varianten werden mit Messwerten **und** eigener Lesbarkeitsbeurteilung verglichen.
- Cppcheck-Meldungen werden anhand des tatsächlichen Befunds klassifiziert; es werden keine nicht beobachteten Warnungen erfunden.
- Gleiche fachliche Risikobewertung wird anhand von Beispielen und dem Vergleichstest erläutert.

## 6. Reflexion – Musterantworten

**Warum ist die niedrigste CCN nicht automatisch die beste Lösung?** Die Kennzahl beschreibt Kontrollflusskomplexität, nicht Fachverständlichkeit, treffende Namen, Modularität oder die Verständlichkeit verschachtelter ternärer Operatoren.

**Was misst NLOC nicht?** Weder die fachliche Richtigkeit noch die Qualität der Abstraktionen; mehr Zeilen können durch sprechende Zwischenschritte die Lesbarkeit verbessern.

**Welche Qualität liefern Tests zusätzlich?** Sie prüfen erwartetes Verhalten für definierte Eingaben. Hohe Abdeckung ist jedoch kein Nachweis, dass die Erwartungen vollständig oder korrekt sind.

**Wie sind Cppcheck-Befunde zu behandeln?** Jeden Hinweis am Code prüfen: tatsächliches Fehlerrisiko, berechtigter Wartungshinweis oder Fehlalarm. Ohne konkreten Bericht ist keine belastbare Klassifizierung möglich.
