# Musterlösung und Nachbesprechung – durchgängige Refactoring-Kette

## Ausgangslage

`ShippingCalculator.calculate` liest wiederholt Getter von `Order` (**Feature Envy**); `Order` ist eine **Data Class**. Versandart als String und Geldbetrag als int zeigen **Primitive Obsession**. Der `switch` ist bei drei Fällen noch nicht zwingend problematisch; entscheidend ist, ob Varianten häufiger erweitert werden.

## Schritt 01: Move Method

Die Versandberechnung wird nach `Order.calculateShipping` verschoben. Die Fassade bleibt bestehen. Ergebnis: Fachliche Daten und Verhalten liegen näher beieinander. Diskutieren: Ein `Order`-Objekt muss nicht zwangsläufig sämtliche Preisregeln kennen.

## Schritt 02: Value Object und Enum

`Money` verhindert negative Werte **innerhalb des Domänenmodells**. Die Fassade bildet negative Eingaben weiterhin auf `-1` ab. `ShippingType.parse` behandelt `null` und unbekannte Strings, sodass das beobachtbare Fehlerverhalten erhalten bleibt. Der Einsatz von `int` für Cent ist hier bewusst gewählt, nicht `double`.

## Schritt 03: Polymorphie

Drei `ShippingStrategy`-Implementierungen kapseln Basispreise. Die Factory verwendet weiterhin einen **einmaligen** `switch`, um die passende Strategie auszuwählen. Das ist legitim. Bewertung: Für dieses kleine Beispiel erhöht die Strategievariante die Anzahl der Klassen; Nutzen entsteht vor allem bei wachsender Variabilität.

## Schritt 04: Extract Class

`ShippingDiscountPolicy` übernimmt die Rabattregel. Vorteil: Regel kann unabhängig von Versandarten geändert und getestet werden. Nachteil: zusätzliche Klasse und Objektbeziehung. Die Entscheidung sollte vom Änderungsbedarf abhängen.

## Unveränderter Verhaltensvertrag

`ShippingCalculatorTest` ist in allen Stufen **identisch**: 14 Testfälle für Versandarten, Inland/Ausland, Rabattgrenze, Abholung und ungültige Eingaben. Die Tests sichern beobachtbares Verhalten, nicht die interne Struktur.

## Vorschlag zur Durchführung

1. Nur Stufe 00 zeigen; Smells und Risiken markieren lassen.
2. Charakterisierungstests ausführen und erwartete Ergebnisse diskutieren.
3. Jede Änderung selbst durchführen lassen; jeweils Tests ausführen.
4. Danach mit der nächsten Stufe vergleichen.
5. Abschlussfrage: Welche Abstraktionen würden Sie in einer echten, kleinen Anwendung beibehalten – und welche zurücknehmen?

**Grenze:** Diese Tests sind ein kleiner, gezielter Verhaltensvertrag, kein vollständiger Nachweis für alle denkbaren `int`-Werte oder künftigen Anforderungen.
