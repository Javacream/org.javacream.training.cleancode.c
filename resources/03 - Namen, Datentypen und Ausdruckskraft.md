# Block 03 – Namen und Datentypen

## Lernziel und Abgrenzung

Versandstatus mit `enum`, Wahrheitswerte mit `bool` und Identifikator mit `unsigned int` ausdrücken. Keine Funktionszerlegung.

## Programmbeispiel

Vergleichen Sie `dirty/03 - Namen, Datentypen und Ausdruckskraft/` und `clean/03 - Namen, Datentypen und Ausdruckskraft/`. Beide Programme sollen dieselbe fachliche Ausgabe erzeugen.

## Aufgabe

Welche Informationen stehen allein im Typ bzw. Bezeichner? Welche Werte sind gültig?

## Reflexion

Welche Verbesserung gehört genau in diesen Block? Welche anderen Verbesserungen würden einen späteren Lernschwerpunkt vorwegnehmen?

## Ausführung mit Laufzeiteingaben

Beide Varianten erwarten vier Zahlen: Status (0=angelegt, 1=verpackt, 2=versendet), Zahlung (0/1), ungültige Adresse (0/1), Sendungsnummer.

```sh
make
./app 2 1 0 3
./app 1 1 0 3
./app 2 0 0 3
./app 2 1 1 3
```

Die Bedingungen sind nun nicht mehr aufgrund fest kodierter Werte konstant wahr. **Der Schwerpunkt bleibt auf Namen und Typen**, nicht auf Funktionszerlegung oder Komplexitätsoptimierung.
