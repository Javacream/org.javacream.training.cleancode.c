# Block 05 – Kontrollfluss und Code-Struktur

## Lernziele
Nach diesem Block können die Teilnehmenden:
- tiefe Verschachtelungen und vermischte Normal- und Fehlerpfade in C90-Code identifizieren;
- Guard Clauses und `switch` als mögliche Strukturierungen vergleichen und eine Wahl begründen;
- für Abholung, Standard und Express sowie für ungültige Fälle die fachlichen Ergebnisse und Fehlercodes überprüfen;
- erklären, weshalb eine geringere Verschachtelung nicht zwingend eine niedrigere zyklomatische Komplexität bedeutet.

## Fachlicher Hintergrund und Abgrenzung
Im Mittelpunkt stehen Kontrollfluss und Verständlichkeit. Guard Clauses machen Vorbedingungen und Fehlerpfade früh sichtbar; ein `switch` kann diskrete Versandarten klar ausdrücken. Nicht jede Umstellung ist automatisch besser.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` mit `clean/`. Versandkosten und Fehlercodes müssen für die vorgesehenen Eingaben einschließlich ungültiger Versandarten erhalten bleiben.

## Aufgabenstellung
1. Zeichnen oder beschreiben Sie die wesentlichen Entscheidungspfade in `dirty`.
2. Identifizieren Sie Fälle, die sich für frühe Rückgaben eignen.
3. Vergleichen Sie die Lesbarkeit der Varianten mit verschachtelten Bedingungen, Guard Clauses und `switch`.
4. Prüfen Sie alle Versandarten für Inland/Ausland sowie gesperrte und ungültige Fälle.
5. Vergleichen Sie die Komplexität und die Verschachtelung; die im Qualitätsbericht ausgewiesene Verschachtelung ist **heuristisch** und keine präzise Parser-Metrik.

## Erfolgskriterien
- Normal- und Fehlerpfade sind eindeutig benannt.
- Die Entscheidung für Guard Clauses oder `switch` ist nachvollziehbar begründet.
- Versandkosten und Fehlercodes stimmen für die geprüften gültigen und ungültigen Fälle überein.
- Die Teilnehmenden können erläutern, warum CCN bei einer strukturellen Verbesserung unverändert bleiben kann.

## Reflexion
Welche Variante lässt sich bei einer neuen Versandart leichter erweitern? Wann wäre eine zusätzliche Dispatch-Struktur überdimensioniert?
