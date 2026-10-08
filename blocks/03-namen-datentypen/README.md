# Block 03 – Namen, Datentypen und Ausdruckskraft

## Lernziele
Nach diesem Block können die Teilnehmenden:
- für Versandstatus, Wahrheitswerte und Identifikatoren geeignete C90-Darstellungen begründet auswählen;
- anhand von Bezeichnern und Typen erklären, welche fachlichen Zustände und Werte gemeint sind;
- mindestens zwei unklare Ausdrücke so umbenennen oder typisieren, dass die Absicht ohne Zusatzkommentar erkennbarer wird;
- für mehrere Eingabekombinationen nachweisen, dass die Versandbereitschaft unverändert berechnet wird.

## Fachlicher Hintergrund und Abgrenzung
C90 besitzt `enum` und `unsigned int`, aber keinen standardisierten `bool`-Typ aus `<stdbool.h>`. Boolesche Aussagen werden hier mit `int` und aussagekräftigen Namen dargestellt. Im Mittelpunkt stehen Namen und Datentypen, **nicht** die Zerlegung von Funktionen oder die Optimierung des Kontrollflusses.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` mit `clean/`. Für alle zulässigen Eingaben muss die Entscheidung über die Versandbereitschaft gleich bleiben.

Beide Varianten erwarten vier Zahlen: Status (0 = angelegt, 1 = verpackt, 2 = versendet), Zahlung (0/1), ungültige Adresse (0/1) und Sendungsnummer.

## Aufgabenstellung
1. Kennzeichnen Sie Bezeichner und Typen, die fachliche Informationen verbergen.
2. Erläutern Sie, welche Zustände durch ein `enum` und welche Werte durch `unsigned int` ausgedrückt werden.
3. Vergleichen Sie die Darstellungen boolescher Bedingungen in `dirty` und `clean`.
4. Führen Sie die Beispiele aus und vergleichen Sie die Ergebnisse:

```sh
make
./app 2 1 0 3
./app 1 1 0 3
./app 2 0 0 3
./app 2 1 1 3
```

## Erfolgskriterien
- Die fachliche Bedeutung von mindestens drei Bezeichnern oder Typentscheidungen ist erläutert.
- Die Grenzen der booleschen Darstellung in C90 werden korrekt benannt.
- Die vier dokumentierten Eingabekombinationen führen in `dirty` und `clean` zu übereinstimmenden Ergebnissen.
- Die Änderungen bleiben auf Benennung und Ausdruckskraft begrenzt.

## Reflexion
Wann hilft ein eigener Typ der Verständlichkeit? Wann erzeugt eine zusätzliche Abstraktion nur Aufwand?
