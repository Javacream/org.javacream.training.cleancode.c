# Block 07 – Testbarer Code und Clean Tests

## Lernziel und Abgrenzung

Original koppelt globalen Steuersatz, Berechnung und Ausgabe. Clean trennt reine Berechnung von I/O, verwendet ein separates Modul und testet Normal-, Rand- und Fehlerfälle. Preise sind ganzzahlige Cent.

## Programmbeispiel

Vergleichen Sie `dirty/07 - Testbarer Code und Clean Tests/` und `clean/07 - Testbarer Code und Clean Tests/`. Beide Programme sollen dieselbe fachliche Ausgabe erzeugen.

## Aufgabe

Führen Sie `make check` in clean aus. Ergänzen Sie einen Test und begründen Sie dessen erwarteten Wert.

## Reflexion

Welche Verbesserung gehört genau in diesen Block? Welche anderen Verbesserungen würden einen späteren Lernschwerpunkt vorwegnehmen?

## Tests und Testabdeckung

```sh
cd "clean/07 - Testbarer Code und Clean Tests"
make check
make coverage
```

`make coverage` kompiliert eine instrumentierte Testanwendung und erzeugt mit `gcov` einen Bericht zur Ausführung von Zeilen und Zweigen in `logic.c`. Die Dirty-Variante besitzt bewusst keine Testsuite; sie erhält daher **keinen künstlichen Coverage-Wert**. Coverage ist keine Aussage über Testqualität.

Diskutieren Sie Grenzwerte, ungültige Eingaben und die Aussagekraft der Assertions.
