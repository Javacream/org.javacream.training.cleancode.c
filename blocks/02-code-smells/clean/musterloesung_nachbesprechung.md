# Block 02 – Code Smells erkennen und beurteilen

## Musterlösung für die Nachbesprechung

**Bezug:** `blocks/02-code-smells/dirty/main.c` und `blocks/02-code-smells/clean/main.c`  
**Ziel:** Code Smells erkennen, von Fehlern unterscheiden, priorisieren und eine begrenzte Verbesserung beurteilen. Umfangreiche Umstrukturierung ist nicht Gegenstand dieses Blocks.

## 1. Ausgangssituation und erwartetes Verhalten

Das Programm berechnet nacheinander zwei Bestellwerte. Bei `process(80, 4, 1, 1)` gelten folgende Regeln:

- Bestellung A: `price * quantity` = 80 × 4 = 320; Premiumrabatt 10 % = 32; Lieferung = 15; **Gesamt 303**.
- Bestellung B: `price * (quantity + 1)` = 80 × 5 = 400; Premiumrabatt 10 % = 40; Lieferung = 15; **Gesamt 375**.
- `last_total` enthält zuletzt den Wert von Bestellung B: **375**.

Erwartete Konsolenausgabe beider Varianten:

```text
Order A: 303
Order B: 375
Last: 375
```

Die unterschiedliche Menge von A und B ist im Beispielcode vorgegeben. Sie ist **kein nachgewiesener Fehler**, auch wenn die fachliche Motivation im echten Projekt geklärt werden müsste.

## 2. Code Smells – beispielhafte Befunde

Die Zeilenangaben beziehen sich auf `dirty/main.c`.

| Fundstelle | Befund | Begründung | Nachgewiesener Bug? |
|---|---|---|---|
| Zeile 2 sowie 10 und 15: `last_total` | Veränderlicher globaler Zustand | Andere Funktionen können den Wert lesen oder verändern; Abhängigkeiten sind nicht an Schnittstellen erkennbar. | Nein |
| Zeilen 7–8 und 13–14 | Doppelte Geschäftsregeln | Rabatt und Lieferzuschlag sind zweimal implementiert. Änderungen könnten nur an einer Stelle erfolgen. | Nein |
| Zeilen 3–18: `process()` | Vermischte Verantwortlichkeiten | Berechnung, Statuspflege und Konsolenausgabe befinden sich in einer Funktion. | Nein |
| Zeile 6: `int unused = total;` und Zeile 17: `(void)unused;` | Unnötige Variable | Die Variable trägt nicht zum Ergebnis bei; `(void)unused` unterdrückt lediglich die Warnung. | Nein |
| Zeile 9: `if (total > 300) total += 0;` | Wirkungsloser Code | Die Addition verändert `total` nicht. | Nein |
| Zeilen 7–8 und 13–14: `10`, `15` | Magic Numbers | Rabattdivisor und Lieferzuschlag sind nicht durch fachlich benannte Konstanten erklärt. | Nein |
| Zeile 3: `process` | Unspezifischer Funktionsname | Der Name verrät weder die Berechnung noch die Ausgabe zweier Bestellungen. | Nein |

**Einordnung:** Ein Code Smell ist ein Indiz für mögliche Wartungsprobleme, kein Beweis für falsches Verhalten. Ein Bug wäre beispielsweise nachgewiesen, wenn für die vereinbarten Eingaben ein falscher Bestellwert ausgegeben würde.

## 3. Priorisierung – mögliche Musterbewertung

| Befund | Auswirkung | Änderungsrisiko | Aufwand | Empfehlung |
|---|---|---|---|---|
| Doppelte Rabatt-/Lieferregel | Hoch: Gefahr inkonsistenter künftiger Änderungen | Mittel | Mittel | Hoch priorisieren, aber Refactoring später durchführen |
| Globaler Zustand | Mittel bis hoch: verdeckte Kopplung | Mittel | Mittel | Dokumentieren und in späterem Block behandeln |
| Wirkungsloser Code | Geringe unmittelbare Auswirkung; erschwert das Lesen | Sehr gering | Sehr gering | Jetzt entfernen |
| Unnötige Variable | Geringe unmittelbare Auswirkung; zusätzlicher Ballast | Sehr gering | Sehr gering | Jetzt entfernen |

Die Priorisierung ist keine starre Rangfolge. Entscheidend ist, dass die Teilnehmenden ihre Entscheidung anhand von **Auswirkung, Änderungsrisiko und Aufwand** nachvollziehbar begründen.

## 4. Begrenzte Verbesserung – Abgleich mit `clean/main.c`

Die Referenzlösung entfernt nur die unnötige Variable und den wirkungslosen Code:

```c
/* Entfernt: */
int unused = total;
if (total > 300) total += 0;
(void)unused;
```

Dies entspricht einer kleinen **Dead-Code-Entfernung**. Der fachliche Berechnungsablauf bleibt unverändert. Die `clean`-Variante behält die doppelte Berechnung und `last_total` bewusst bei, damit die weiterführenden Refactoring-Themen nicht vorweggenommen werden.

**Mögliche Nebenwirkung:** Beim Entfernen von vermeintlich unnötigem Code muss geprüft werden, ob Ausdrücke Seiteneffekte haben. Hier sind weder die Initialisierung der nur lokal verwendeten Variable noch die Bedingung oder die Addition von null für die definierte Ausgabe relevant.

## 5. Erfolgskriterien und Nachweise

| Erfolgskriterium | Nachweis in der Nachbesprechung |
|---|---|
| Mindestens drei konkrete Code Smells | Fundstellen aus Abschnitt 2 mit Erklärung |
| Smell von Bug unterscheiden | Beispielsweise erläutern, warum `total += 0` unnötig, aber keine falsche Berechnung ist |
| Zwei Befunde priorisieren | Begründete Bewertung von Auswirkung, Risiko und Aufwand |
| Begrenzte Verbesserung auswählen | Entfernen der unnötigen Variable und/oder der wirkungslosen Anweisung |
| Verhalten erhalten | Beide Varianten erzeugen `303`, `375`, `375` |
| Umfang der Übung beachten | Globale Variable und Duplikation bleiben für spätere Blöcke bestehen |

### Praktischer Abgleich

In den Verzeichnissen `dirty/` und `clean/` jeweils ausführen:

```sh
make clean
make test
```

**Wichtig:** Das vorhandene `make test` startet lediglich die Anwendung. Es enthält **keine automatische Prüfung** der Sollausgabe. Für die Nachbesprechung ist die Ausgabe deshalb mit dem obigen Verhaltensvertrag zu vergleichen. Ein automatisierter Ausgabevergleich wäre eine mögliche spätere Ergänzung.

## 6. Reflexion – Musterantworten

**Warum ist die doppelte Rabattberechnung problematisch, obwohl die Ergebnisse korrekt sind?**  
Weil eine Änderung der Rabattregel an zwei Stellen vorgenommen werden muss. Wird eine Stelle übersehen, können widersprüchliche Ergebnisse entstehen. Der Smell erhöht das Wartungsrisiko, ohne bereits einen Fehler nachzuweisen.

**Warum sollte `last_total` nicht sofort entfernt werden?**  
Die globale Variable erzeugt eine verdeckte Abhängigkeit zwischen `process()` und `main()`. Ihre Beseitigung erfordert eine bewusste Neugestaltung der Datenübergabe. Das passt besser zu späteren Blöcken über Funktionen und Refactoring.

**Ist `total += 0` immer gefahrlos entfernbar?**  
In diesem konkreten Programm ja: Die Anweisung verändert den Wert nicht. Allgemein muss vor dem Entfernen vermeintlich wirkungsloser Anweisungen auf Seiteneffekte und den relevanten Verhaltensvertrag geachtet werden.

**Warum ist `clean/main.c` noch nicht vollständig „clean“?**  
Weil nur offensichtlicher Ballast entfernt wurde. Doppelte Geschäftsregeln, globaler Zustand, Magic Numbers und vermischte Verantwortlichkeiten bleiben bestehen. Die Referenzversion demonstriert bewusst eine begrenzte Verbesserung.

**Wann sollte ein erkannter Code Smell zunächst bestehen bleiben?**  
Wenn die Änderung ein größeres Risiko als den erwarteten Nutzen erzeugt, die Anforderungen unklar sind oder ausreichende Tests fehlen. Die Entscheidung sollte dokumentiert und bei künftigen Änderungen überprüft werden.

## 7. Kernaussage für die Nachbesprechung

**Code Smells sind Anlass für eine begründete technische Entscheidung, nicht automatisch ein Änderungsauftrag.** In Block 02 stehen Diagnose und Priorisierung im Mittelpunkt. Eine kleine, verhaltenserhaltende Bereinigung genügt; weitergehendes Refactoring folgt später.
