# Block 08 – Refactoring und kontinuierliche Verbesserung

## Lernziele
Nach diesem Block können die Teilnehmenden:
- aus mehreren Code Smells einen begründeten Refactoring-Plan mit kleinen, überprüfbaren Schritten ableiten;
- vor der ersten Änderung vorhandene Charakterisierungstests ausführen;
- mindestens zwei unterschiedliche Strukturverbesserungen nacheinander durchführen und nach jedem Schritt erneut testen;
- eine unbeabsichtigte Verhaltensänderung von einer rein strukturellen Verbesserung unterscheiden;
- die eigene Lösung mit `clean` vergleichen und Vor- und Nachteile begründen.

## Fachlicher Hintergrund und Abgrenzung
Refactoring verbessert die innere Struktur, ohne das beobachtbare Verhalten zu verändern. Hier werden bekannte Techniken kombiniert: bessere Namen, Guard Clauses, Funktionszerlegung und benannte Konstanten. Es werden **keine neuen fachlichen Anforderungen** eingeführt. Die [Code-Smell-Refactoring-Matrix](../../CODE-SMELL-REFACTORING-MATRIX.md) unterstützt die Auswahl, schreibt aber keine Lösung vor.

## Ausgangssituation und Verhaltensvertrag
Vergleichen Sie `dirty/` mit `clean/`. Charakterisierungstests liegen für beide Varianten vor. Die Bestellberechnung und die übrigen definierten Ergebnisse müssen nach **jedem** Refactoring-Schritt unverändert bleiben.

## Aufgabenstellung
1. Führen Sie zunächst in `dirty` `make check` aus und halten Sie den Ausgangszustand fest.
2. Identifizieren und priorisieren Sie die wichtigsten Strukturprobleme.
3. Planen Sie mindestens zwei kleine, voneinander getrennte Refactoring-Schritte und begründen Sie deren Reihenfolge.
4. Führen Sie die Schritte einzeln durch. Starten Sie nach **jedem** Schritt die Tests und korrigieren Sie etwaige Regressionen, bevor Sie fortfahren.
5. Vergleichen Sie erst anschließend mit `clean` und diskutieren Sie unterschiedliche zulässige Lösungen.

## Erfolgskriterien
- Ein kurzer, nachvollziehbarer Refactoring-Plan liegt vor.
- Mindestens zwei getrennte Änderungen sind fachlich begründet.
- Die Charakterisierungstests laufen vor und nach jedem Schritt erfolgreich.
- Die Teilnehmenden können die Verbesserung anhand von Verständlichkeit und Änderbarkeit erläutern, nicht nur anhand von Zeilenzahlen.

## Reflexion
Welche Änderungen hätten Sie bewusst **nicht** vorgenommen? Welche fachlichen Risiken bleiben trotz erfolgreicher Tests bestehen?
