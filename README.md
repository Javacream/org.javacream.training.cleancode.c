# Clean Code – OOP Code Smells und Refactoring (Java 21)

Durchgängige Fallstudie zur **Versandkostenberechnung**. Jede Stufe ist ein eigenständig ausführbares Maven-Projekt mit denselben Charakterisierungstests. Die Java-Projekte benötigen nur JDK 21, Maven und JUnit 5.

| Stufe | Fokus | Auffälligkeit / Refactoring |
|---|---|---|
| [00-ausgangslage](00-ausgangslage/) | Analyse | Feature Envy, Primitive Obsession, Switch, Large Class |
| [01-move-method](01-move-method/) | Verantwortlichkeit | Move Method: Berechnung in das Order-Objekt |
| [02-value-objects](02-value-objects/) | Domänenmodell | Replace Primitive with Object / enum: Money und ShippingType |
| [03-polymorphism](03-polymorphism/) | Variation | Replace Conditional with Polymorphism: Versandstrategien |
| [04-extract-class](04-extract-class/) | Kohäsion | Extract Class: Versandrabatt als eigenständige Policy |

**Reihenfolge:** Erst den Code der Ausgangslage untersuchen, dann Stufe für Stufe refactoren. Die nachfolgende Stufe dient als Musterlösung für den jeweiligen Schritt. Die Tests sind in allen Stufen wortgleich.

In jedem Stufenverzeichnis: `mvn test`. Mit `mvn -q exec:java -Dexec.mainClass=org.javacream.training.oop.shipping.Application` lässt sich das Beispielprogramm starten.

[Verhaltensvertrag](VERHALTENSVERTRAG.md) · [Trainerhinweise](instructor/README.md)

**Hinweis:** Der Wechsel von primitiven Typen zu Objekten und Strategien verändert interne Java-APIs. Gleich bleiben die extern beobachtbaren Versandkosten, die über `ShippingCalculator.calculate(int, String, boolean, boolean)` abgefragt werden. Das ist eine bewusst stabil gehaltene Fassade für die Charakterisierungstests.
