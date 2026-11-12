# Übung – Rechteckberechnung mit testbarer Struktur

## Aufgabe

Implementierung einer C90-Anwendung zur Berechnung von **Fläche** und **Umfang** eines Rechtecks mit den Seitenlängen `a` und `b`. Die Anwendung soll von Beginn an testbar und klar strukturiert sein.

Die `main`-Funktion verwendet **a = 5** und **b = 37**. Erwartete Ergebnisse:

- Fläche: **185**
- Umfang: **84**

## Aufbau

- `rectangle.h`: öffentliche Funktionsdeklarationen.
- `rectangle.c`: reine Berechnungsfunktionen ohne Ein-/Ausgabe und globale Variablen.
- `main.c`: Anwendungsstart, Beispielwerte und Ausgabe.
- `test.c`: eigenständige Tests der Berechnungsfunktionen, ohne `main.c` aufzurufen.
- `Makefile`: Build und Test.

Die Testfälle prüfen das vorgegebene Rechteck, ein Quadrat, eine Seite der Länge null und gebrochene Seitenlängen. Die API setzt nicht negative Seitenlängen voraus; für negative Eingaben wird kein gesonderter Fehlervertrag definiert.

## Ausführung

Im Verzeichnis `blocks/07-testbarkeit/exercise`:

```sh
make
make run
make test
make clean
```

## Clean-Code-Aspekte

Die Fachlogik ist unabhängig von `stdio` und der Konsolenausgabe. Die Funktionsnamen benennen ihre Verantwortung, und die Tests greifen ausschließlich auf die öffentliche Schnittstelle zu. Für die gewählten, exakt binär darstellbaren Testwerte ist ein direkter Vergleich der `double`-Ergebnisse möglich; bei allgemeinen Gleitkommarechnungen wäre ein toleranzbasierter Vergleich sinnvoll.
