# 04 – Extract Class

Die Rabattregel wird aus `Order` in `ShippingDiscountPolicy` extrahiert. Die Order koordiniert Validierung, Strategie und Rabatt.

**Smell / Technik:** Large Class / Divergent Change → Extract Class.

**Aufgabe:** Prüfen Sie, ob die zusätzliche Klasse eine eigenständige fachliche Verantwortung besitzt oder nur zusätzliche Indirektion erzeugt.

**Test:** `mvn test` (in diesem Verzeichnis). Die Tests sind in allen fünf Stufen identisch. Der vollständige [Verhaltensvertrag](../VERHALTENSVERTRAG.md) gilt durchgehend.

**Nächster Schritt:** Abschlussreview: Verbesserungen und neue Abstraktionskosten abwägen.
