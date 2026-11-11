# 00 – Ausgangslage

Analysieren Sie `ShippingCalculator` und `Order`. Die Berechnung greift mehrfach auf fremde Daten zu; Versandarten und Beträge sind primitiv modelliert, und die Berechnung enthält eine Fallunterscheidung.

**Smell / Technik:** Feature Envy, Data Class, Primitive Obsession, Switch Statements, Magic Numbers.

**Aufgabe:** Markieren Sie mindestens vier Fundstellen. Formulieren Sie eine Priorisierung und führen Sie `mvn test` aus.

**Test:** `mvn test` (in diesem Verzeichnis). Die Tests sind in allen fünf Stufen identisch. Der vollständige [Verhaltensvertrag](../VERHALTENSVERTRAG.md) gilt durchgehend.

**Nächster Schritt:** [01-move-method](../01-move-method/)
