# Katalog gängiger OOP-Refactoring-Patterns

Die Bezeichnungen sind gebräuchliche Refactoring-Techniken, keine Entwurfsmuster im engeren GoF-Sinn. Die Techniken sollten **kleinschrittig und testgesichert** angewendet werden.

| Refactoring | Ausgangssituation | Veränderung | Risiko / Prüfpunkt |
|---|---|---|---|
| Move Method | Methode nutzt überwiegend Daten einer anderen Klasse | Methode zum fachlich zuständigen Objekt verschieben | Sichtbarkeit, Abhängigkeiten, öffentliche API |
| Extract Method | Lange Methode mit mehreren Aufgaben | Benannten Teil in Methode auslagern | Reihenfolge und Seiteneffekte |
| Extract Class | Klasse hat mehrere Verantwortlichkeiten | Zusammengehörige Daten und Methoden in eigene Klasse verschieben | Neue Kopplung und überflüssige Indirektion |
| Inline Class | Klasse bietet kaum eigenen Nutzen | Verhalten in eine andere Klasse integrieren | Schnittstellen und Namenskonflikte |
| Encapsulate Field / Variable | Daten sind direkt manipulierbar | Zugriff über kontrollierte Methoden | Invarianten und Kompatibilität |
| Replace Primitive with Object | Fachwert als `int` oder `String` | Value Object mit Validierung einführen | Konvertierung, Equality, Null-Verhalten |
| Replace Type Code with Enum | String- oder Zahlenkonstanten für Zustände | `enum` einführen | Ungültige Eingaben am Systemrand |
| Introduce Parameter Object | Wiederkehrende Parametergruppe | Zusammengehörige Parameter bündeln | Nicht zusammengehörige Werte nicht künstlich koppeln |
| Replace Conditional with Polymorphism | Wiederholte Fallunterscheidung nach Typ | Varianten als Untertypen oder Strategien modellieren | Mehr Klassen, Factory und Indirektion |
| Replace Inheritance with Delegation | Vererbung bildet keine echte Ist-ein-Beziehung | Verhalten über Komposition beziehen | Delegationsaufwand |
| Pull Up Method | Gleiches Verhalten in Unterklassen | Gemeinsame Methode in Oberklasse | Gemeinsamer Vertrag muss gelten |
| Push Down Method | Oberklasse enthält spezialisiertes Verhalten | Methode in passende Unterklasse verschieben | Substituierbarkeit |
| Hide Delegate | Klienten navigieren lange Objektketten | Geeignete Delegationsmethode anbieten | Gefahr eines Middle Man |
| Remove Middle Man | Klasse leitet fast nur Aufrufe weiter | Direkten Zugriff ermöglichen | Kapselung nicht unnötig schwächen |
| Replace Constructor with Factory Function | Konstruktion benötigt Auswahl/Benennung | Erzeugung über Factory kapseln | Zusätzliche Abstraktion |
| Separate Query from Modifier | Methode liest und verändert Zustand zugleich | Abfrage und Zustandsänderung trennen | Aufrufreihenfolge und Nebenwirkungen |
| Introduce Null Object | Viele wiederholte Nullprüfungen | Explizites Objekt für fehlendes Verhalten | Null und fachliche Abwesenheit unterscheiden |
| Extract Interface | Mehrere Klienten brauchen stabilen Vertrag | Abhängigkeit von Schnittstelle statt Implementierung | Abstraktion ohne echte Variabilität |

## Empfohlene Reihenfolge in der Fallstudie

1. **Move Method** – Berechnung nach `Order` (Stufe 01).
2. **Replace Primitive with Object / Enum** – `Money`, `ShippingType` (Stufe 02).
3. **Replace Conditional with Polymorphism** – `ShippingStrategy` (Stufe 03).
4. **Extract Class** – `ShippingDiscountPolicy` (Stufe 04).

**Nicht jedes Refactoring ist zwingend eine Verbesserung.** Für drei feste Versandarten kann ein `switch` klarer sein als eine Strategiehierarchie. Das ist ein bewusstes Review-Thema.

Quellen: Martin Fowler, *Refactoring: Improving the Design of Existing Code*, 2. Auflage (2018), [Refactoring Catalog](https://refactoring.com/catalog/); [Refactoring.Guru](https://refactoring.guru/refactoring/techniques).
