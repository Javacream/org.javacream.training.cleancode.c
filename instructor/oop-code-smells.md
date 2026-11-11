# Gängige OOP Code Smells

Ein Code Smell ist ein **Indikator**, kein bewiesener Defekt. Die Begriffe orientieren sich unter anderem an Martin Fowler und Refactoring.Guru.

| Code Smell | Erkennungsmerkmal | Mögliche Folge | Typisches Refactoring |
|---|---|---|---|
| Feature Envy | Methode nutzt überwiegend Daten einer fremden Klasse | Fehlplatzierte Verantwortung | Move Method |
| Data Class | Klasse besteht fast nur aus Daten und Zugriffsmethoden | Anämisches Domänenmodell | Move Method, Encapsulate Field |
| Primitive Obsession | Strings und Zahlen ersetzen Fachtypen | Ungültige Werte, fehlende Typprüfung | Replace Primitive with Object, Enum |
| Large Class | Klasse übernimmt zu viele Aufgaben | Geringe Kohäsion, hoher Änderungsaufwand | Extract Class |
| Long Method | Viele Aufgaben in einer Methode | Schlechte Verständlichkeit | Extract Method |
| Long Parameter List | Viele einzelne Parameter | Verwechslungsgefahr | Introduce Parameter Object |
| Inappropriate Intimacy | Klassen kennen gegenseitig Interna | Enge Kopplung | Move Method, Hide Delegate |
| Message Chains | Lange Aufrufketten über mehrere Objekte | Strukturabhängigkeit | Hide Delegate |
| Middle Man | Klasse delegiert nahezu ausschließlich | Unnötige Indirektion | Remove Middle Man |
| Refused Bequest | Unterklasse benötigt geerbtes Verhalten nicht | Unpassende Vererbung | Replace Inheritance with Delegation |
| Parallel Inheritance Hierarchies | Jede neue Unterklasse erzwingt weitere Unterklassen | Aufwendige Erweiterungen | Move Method, Entkopplung |
| Repeated Switches | Typunterscheidungen an mehreren Stellen | Verstreute Änderungen | Replace Conditional with Polymorphism |
| Divergent Change | Klasse ändert sich aus unabhängigen Gründen | Verletzung der Kohäsion | Extract Class |
| Shotgun Surgery | Eine Regeländerung erfordert viele Klassenänderungen | Hohe Fehlergefahr | Move Method, Inline Class |
| Temporary Field | Attribute gelten nur in manchen Zuständen | Unklare Objektinvarianten | Extract Class |
| Speculative Generality | Abstraktionen ohne tatsächlichen Bedarf | Mehr Komplexität als Nutzen | Collapse Hierarchy, Inline Class |
| Mutable Data | Unkontrollierte Zustandsänderungen | Reihenfolgeabhängigkeit | Encapsulate Variable, Immutable Value Object |
| Duplicated Code | Gleiche Logik an mehreren Stellen | Inkonsistente Änderungen | Extract Method, Pull Up Method |

## Bezug zur Fallstudie

- **00:** Feature Envy, Data Class, Primitive Obsession, Switch Statements.
- **01:** Verantwortung nach `Order` verschoben; die Fassade delegiert absichtlich, um den Testvertrag zu erhalten.
- **02:** `Money` und `ShippingType` machen Fachkonzepte explizit.
- **03:** Strategien ersetzen die Versandarten-Fallunterscheidung; die einmalige Auswahl im Factory-Code ist kein automatisch zu beseitigender Smell.
- **04:** Rabattregel ist in einer eigenen Policy gekapselt. Kritisch prüfen, ob die Extraktion wirklich nötig ist.

**Diskussionsfrage:** Eine neue Klasse kann einen Smell beheben und gleichzeitig einen neuen verursachen, etwa *Middle Man* oder *Speculative Generality*.

Quellen: Martin Fowler, *Refactoring*, 2. Auflage; [Refactoring.Guru – Code Smells](https://refactoring.guru/refactoring/smells).
