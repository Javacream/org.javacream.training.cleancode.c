# Block 04 – Funktionen und Verantwortlichkeiten

## Lernziele
Nach diesem Block können die Teilnehmenden:
- in einer Bestellverarbeitung Validierung, Berechnung und Ausgabe als unterschiedliche Verantwortlichkeiten identifizieren;
- eine sinnvolle Funktionsaufteilung mit klaren Eingaben und Ergebnissen begründen;
- erklären, wann ein zusammengehöriger Datensatz wie `Order` einer langen Parameterliste vorzuziehen ist;
- nachweisen, dass die Ausgabeoption `print_details` sowohl für 0 als auch für 1 erhalten bleibt.

## Fachlicher Hintergrund und Abgrenzung
Funktionen sollen einen nachvollziehbaren Zweck erfüllen. Eine Zerlegung ist nur dann sinnvoll, wenn sie Verantwortlichkeiten trennt und die Lesbarkeit verbessert. Der Ablauf bleibt bewusst einfach; neue Fehlerbehandlung oder Kontrollflussoptimierung ist nicht Ziel dieses Blocks.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` und `clean/`. Die fachliche Bestellberechnung und die optionale Detailausgabe müssen erhalten bleiben.

## Aufgabenstellung
1. Kennzeichnen Sie die Anteile für Validierung, Berechnung und Ausgabe in `dirty`.
2. Entwerfen Sie Funktionsgrenzen und erläutern Sie die benötigten Parameter und Rückgabewerte.
3. Prüfen Sie, ob `Order` fachlich zusammengehörige Daten bündelt.
4. Vergleichen Sie mit `clean` und prüfen Sie ausdrücklich beide Zustände von `print_details`.

## Erfolgskriterien
- Mindestens drei Verantwortlichkeiten sind im Ausgangscode benannt.
- Die vorgeschlagenen Funktionsgrenzen sind fachlich begründet; bloße Zeilenverkürzung zählt nicht.
- Die Bestellberechnung bleibt unverändert.
- `print_details = 0` und `print_details = 1` zeigen weiterhin das jeweils vorgesehene Verhalten.

## Reflexion
Woran erkennt man, dass eine zusätzliche Funktion eine sinnvolle Abstraktion ist? Wann verschlechtert eine Zerlegung die Verständlichkeit?
