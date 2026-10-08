# Block 02 – Code Smells erkennen und beurteilen

## Lernziele
Nach diesem Block können die Teilnehmenden:
- in einem C90-Programm mindestens drei konkrete Hinweise auf Wartbarkeitsprobleme (z. B. doppelte Berechnung, globaler Zustand, redundante Anweisung, lange Funktion) mit Fundstelle benennen;
- zwischen einem Code Smell und einem nachgewiesenen Fehler unterscheiden;
- mindestens zwei Befunde anhand von Auswirkung, Änderungsrisiko und Aufwand priorisieren;
- eine passende Refactoring-Technik vorschlagen und erläutern, weshalb eine sofortige Änderung sinnvoll oder nicht sinnvoll ist.

## Fachlicher Hintergrund und Abgrenzung
Ein Code Smell ist ein Hinweis auf ein mögliches Strukturproblem, kein automatischer Fehlernachweis. Die `clean`-Variante entfernt hier bewusst nur offensichtlichen Ballast. Umfangreiche Umstrukturierungen sind Gegenstand späterer Blöcke. Als Orientierung dient die [Code-Smell-Refactoring-Matrix](../../CODE-SMELL-REFACTORING-MATRIX.md).

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` und `clean/`. Beide Varianten sollen dieselben fachlich definierten Bestellergebnisse liefern; das Entfernen redundanter Anweisungen darf das Verhalten nicht ändern.

## Aufgabenstellung
1. Untersuchen Sie zunächst nur `dirty` und markieren Sie mindestens drei konkrete Fundstellen.
2. Beschreiben Sie zu jeder Fundstelle das mögliche Problem und prüfen Sie, ob ein tatsächlicher Fehler vorliegt.
3. Priorisieren Sie zwei Befunde anhand nachvollziehbarer Kriterien.
4. Schlagen Sie für einen Befund eine begrenzte Verbesserung vor. Ordnen Sie ihr eine Technik aus der Matrix zu und benennen Sie eine mögliche Nebenwirkung.
5. Vergleichen Sie erst danach mit `clean` und überprüfen Sie die fachliche Ausgabe.

## Erfolgskriterien
- Mindestens drei Befunde sind mit Fundstelle und Begründung dokumentiert.
- Mindestens zwei Befunde sind nachvollziehbar priorisiert.
- Die Unterscheidung zwischen Smell und Bug wird an einem Beispiel erläutert.
- Die ausgewählte Verbesserung ist begründet und die relevante Ausgabe bleibt unverändert.

## Reflexion
Welche Änderungen würden den Lernschwerpunkt späterer Blöcke vorwegnehmen? Wann ist es sinnvoll, einen erkannten Smell vorerst nicht zu beseitigen?
