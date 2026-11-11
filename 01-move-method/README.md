# 01 – Move Method

Die Versandberechnung ist von `ShippingCalculator` nach `Order.calculateShipping()` verschoben. `ShippingCalculator` bleibt als stabile Fassade bestehen.

**Smell / Technik:** Feature Envy / Data Class → Move Method.

**Aufgabe:** Vergleichen Sie die Verantwortlichkeiten. Warum ist die Verschiebung hier plausibel? Wann wäre ein eigenständiger Domänenservice besser?

**Test:** `mvn test` (in diesem Verzeichnis). Die Tests sind in allen fünf Stufen identisch. Der vollständige [Verhaltensvertrag](../VERHALTENSVERTRAG.md) gilt durchgehend.

**Nächster Schritt:** [02-value-objects](../02-value-objects/)
