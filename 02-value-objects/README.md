# 02 – Value Objects

`Money` kapselt Cent-Beträge; `ShippingType` ersetzt freie Strings. Die Fassade übersetzt externe Eingaben und behandelt ungültige Werte.

**Smell / Technik:** Primitive Obsession → Replace Primitive with Object / Replace Type Code with Enum.

**Aufgabe:** Vergleichen Sie die Typverträge und diskutieren Sie den Vorteil gegenüber `int`/`String`. Die interne API ändert sich, das Testergebnis nicht.

**Test:** `mvn test` (in diesem Verzeichnis). Die Tests sind in allen fünf Stufen identisch. Der vollständige [Verhaltensvertrag](../VERHALTENSVERTRAG.md) gilt durchgehend.

**Nächster Schritt:** [03-polymorphism](../03-polymorphism/)
