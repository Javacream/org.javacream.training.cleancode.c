# 03 – Polymorphie

`ShippingStrategy` und drei Implementierungen übernehmen die variierenden Basispreise. Die Auswahl erfolgt einmal zentral über `ShippingStrategies`.

**Smell / Technik:** Repeated Conditional / Switch → Replace Conditional with Polymorphism.

**Aufgabe:** Bewerten Sie den Trade-off: drei kleine Klassen statt eines kompakten `switch`. Diskutieren Sie, ob Polymorphie in diesem Fall gerechtfertigt ist.

**Test:** `mvn test` (in diesem Verzeichnis). Die Tests sind in allen fünf Stufen identisch. Der vollständige [Verhaltensvertrag](../VERHALTENSVERTRAG.md) gilt durchgehend.

**Nächster Schritt:** [04-extract-class](../04-extract-class/)
