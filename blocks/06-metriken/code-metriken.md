# Übersicht gebräuchlicher Code-Metriken

Diese Übersicht beschreibt verbreitete Metriken zur Beurteilung von Quellcode und seiner Wartbarkeit. Die Werte sind **Indikatoren**, keine allgemeingültigen Qualitätsnoten. Definition, Zählweise und Schwellenwerte können je nach Analysewerkzeug abweichen.

## Umfang und Größe

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| LOC | Lines of Code | Gesamtzahl der Quellcodezeilen; je nach Werkzeug einschließlich oder ausschließlich Leerzeilen und Kommentaren. |
| SLOC / LLOC | Source Lines of Code / Logical Lines of Code | Physische beziehungsweise logische Codezeilen. Logische Zeilen orientieren sich an Anweisungen statt an Zeilenumbrüchen; die genaue Definition ist werkzeugabhängig. |
| NLOC | Non-comment Lines of Code | Zeilen ohne reine Kommentare und typischerweise ohne Leerzeilen. Bei Lizard eine gebräuchliche Größenmetrik für Funktionen. |
| NOS | Number of Statements | Anzahl der Anweisungen in einer Funktion oder Komponente. Zeigt Umfang unabhängig von der Formatierung. |
| NOM | Number of Methods | Anzahl der Methoden einer Klasse; relevant für objektorientierte Sprachen wie Java. |
| NOC (Klassenumfang) | Number of Classes | Anzahl der Klassen in einem Modul oder Projekt. **Nicht verwechseln** mit dem gleichlautenden Kürzel NOC aus den Chidamber-Kemerer-Metriken. |

## Komplexität und Kontrollfluss

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| CC / CCN / VG | Cyclomatic Complexity / Cyclomatic Complexity Number / McCabe's V(G) | Misst die Zahl linear unabhängiger Pfade im Kontrollflussgraphen. Verzweigungen erhöhen typischerweise den Wert. Zählregeln für logische Operatoren unterscheiden sich zwischen Werkzeugen. |
| CogC / Cognitive Complexity | Cognitive Complexity | Schätzt die mentale Belastung beim Verstehen des Kontrollflusses. Berücksichtigt unter anderem Verschachtelung; ist **nicht** identisch mit CCN. |
| ND / NEST | Nesting Depth | Tiefe verschachtelter Kontrollstrukturen wie `if`, `for` oder `while`. Eine einfache Heuristik ist nicht mit einer vollständigen Parseranalyse gleichzusetzen. |
| EV(G) | Essential Complexity | Bewertet, wie stark der Kontrollfluss von gut strukturierten Konstrukten abweicht; weniger verbreitet als CCN. |
| NP / NPath | NPath Complexity | Anzahl möglicher azyklischer Ausführungspfade innerhalb einer Funktion. Kann durch Kombinationen von Bedingungen stark wachsen. |

## Schnittstellen und Kopplung

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| PARAM / NP | Number of Parameters | Anzahl der Parameter einer Funktion oder Methode. Viele Parameter können auf schwer verständliche Schnittstellen oder fehlende Datenabstraktion hinweisen. |
| FAN-IN | Fan-in | Anzahl der Stellen beziehungsweise Komponenten, die eine Funktion oder Komponente aufrufen oder von ihr abhängen; die genaue Definition variiert. |
| FAN-OUT | Fan-out | Anzahl der unterschiedlichen Funktionen oder Komponenten, die eine Funktion oder Komponente verwendet. Hohe Werte können starke Abhängigkeiten anzeigen. |
| CBO | Coupling Between Object Classes | Anzahl anderer Klassen, mit denen eine Klasse gekoppelt ist. Hohe Kopplung kann Änderungen und isolierte Tests erschweren. |
| RFC | Response For a Class | Anzahl der Methoden, die als Reaktion auf eine Nachricht an eine Klasse potenziell ausgeführt werden können; klassische OOP-Metrik nach Chidamber und Kemerer. |
| Ca / Ce | Afferent Coupling / Efferent Coupling | Eingehende beziehungsweise ausgehende Abhängigkeiten eines Pakets oder Moduls. Dienen zur Beurteilung von Architekturkopplung. |
| I | Instability | Häufig definiert als `Ce / (Ca + Ce)`. Werte nahe 1 bedeuten überwiegend ausgehende, Werte nahe 0 überwiegend eingehende Abhängigkeiten; bei `Ca + Ce = 0` nicht definiert. |

## Objektorientierte Struktur (insbesondere Java)

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| WMC | Weighted Methods per Class | Summe der Komplexitäten der Methoden einer Klasse. Bei Gewicht 1 pro Methode entspricht der Wert der Methodenanzahl. |
| DIT | Depth of Inheritance Tree | Tiefe einer Klasse in der Vererbungshierarchie. Große Tiefe kann das Nachvollziehen geerbten Verhaltens erschweren. |
| NOC (Vererbung) | Number of Children | Anzahl unmittelbarer Unterklassen einer Klasse; klassische Chidamber-Kemerer-Metrik. |
| LCOM | Lack of Cohesion in Methods | Maß für fehlenden Zusammenhalt der Methoden einer Klasse, häufig anhand gemeinsam verwendeter Attribute. Es existieren mehrere **nicht direkt vergleichbare** LCOM-Varianten. |
| TCC / LCC | Tight Class Cohesion / Loose Class Cohesion | Anteil direkt beziehungsweise direkt oder indirekt zusammenhängender Methodenpaare einer Klasse. Bewertet den inneren Zusammenhalt. |
| ATFD | Access to Foreign Data | Anzahl der Zugriffe einer Klasse oder Methode auf Daten fremder Klassen; kann auf *Feature Envy* hinweisen. |

## Wartbarkeit und Duplikation

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| MI | Maintainability Index | Zusammengesetzter Wartbarkeitsindex, häufig aus Umfang, zyklomatischer Komplexität und Halstead-Metriken. Formel und Skala variieren stark zwischen Werkzeugen. |
| HV | Halstead Volume | Aus Operatoren und Operanden berechnetes Maß für den Informationsumfang eines Programms. |
| HD | Halstead Difficulty | Aus der Anzahl unterschiedlicher und verwendeter Operatoren/Operanden abgeleitete Schwierigkeit nach Halstead. |
| HE | Halstead Effort | Abgeleiteter Aufwand nach Halstead, üblicherweise `Difficulty × Volume`; keine verlässliche reale Zeitschätzung. |
| DUP / DR | Duplicated Lines / Duplication Ratio | Anzahl beziehungsweise Anteil duplizierter Codezeilen oder Blöcke. Die Erkennung hängt von Mindestlänge und Vergleichsverfahren ab. |

## Tests und Qualitätssicherung

| Kurzname / Abkürzung | Ausgeschriebener Name | Erläuterung |
|---|---|---|
| LC / C0 | Line Coverage / Statement Coverage | Anteil ausgeführter Codezeilen beziehungsweise Anweisungen durch Tests. Die beiden Begriffe sind verwandt, aber nicht in jedem Werkzeug identisch. |
| BC / C1 | Branch Coverage | Anteil ausgeführter Entscheidungszweige. Vollständige Branch Coverage garantiert nicht die Prüfung aller Pfadkombinationen. |
| FC | Function Coverage | Anteil der mindestens einmal ausgeführten Funktionen. |
| MC/DC | Modified Condition/Decision Coverage | Prüft, ob jede atomare Bedingung den Ausgang einer Entscheidung unabhängig beeinflussen kann; besonders in sicherheitskritischen Systemen gebräuchlich. |
| MS | Mutation Score | Anteil erkannter beziehungsweise getöteter Mutanten bei Mutationstests; aussagekräftiger für die Fehlererkennung von Tests als reine Coverage, aber abhängig von den Mutationsoperatoren. |
| DD / Defect Density | Defect Density | Anzahl bekannter Fehler pro definierter Größenbasis, oft pro 1.000 LOC. Hängt stark von Erfassungsprozess und Fehlerdefinition ab. |

## Einordnung für diesen Kurs

Im vorhandenen **Block 06** werden insbesondere folgende Metriken praktisch betrachtet:

- **Lizard:** NLOC, CCN und Parameteranzahl.
- **Kursskript `analyze.py`:** zusätzliche *heuristische* Verschachtelungstiefe.
- **Cppcheck:** Statische Analysebefunde, **keine einzelne Code-Metrik**.

Cognitive Complexity, Halstead-Metriken, Kopplungs- und OOP-Metriken sind hier als **ergänzender Überblick** aufgeführt. Ihre Erwähnung bedeutet nicht, dass die bestehende Kursumgebung sie bereits berechnet.

### Hinweise zur Interpretation

1. **Vergleiche nur gleich definierte Messungen.** Unterschiedliche Werkzeuge können für dieselbe Funktion verschiedene Werte ermitteln.
2. **Betrachte Messwerte im Kontext.** Eine niedrige CCN kann mit schwer lesbaren Ausdrücken einhergehen; eine höhere NLOC kann durch klarere Zwischenschritte entstehen.
3. **Unterscheide Funktion, Klasse und Projekt.** Ein Maximalwert je Funktion lässt sich nicht ohne Weiteres mit einem Projektmittelwert vergleichen.
4. **Nutze Tests und Reviews ergänzend.** Coverage misst ausgeführten Code, nicht die fachliche Richtigkeit der Assertions.
5. **Leite aus einzelnen Grenzwerten keine automatischen Refactoring-Pflichten ab.** Aussagekräftiger sind auffällige Entwicklungen, konkrete Code Smells und das Änderungsrisiko.

### Weiterführende Quellen

- Thomas J. McCabe: *A Complexity Measure* (1976).
- Maurice H. Halstead: *Elements of Software Science* (1977).
- Shyam R. Chidamber, Chris F. Kemerer: *A Metrics Suite for Object Oriented Design* (1994).
- [Lizard – Code Complexity Analyzer](https://github.com/terryyin/lizard).
- [SonarSource – Cognitive Complexity](https://www.sonarsource.com/resources/cognitive-complexity/).
