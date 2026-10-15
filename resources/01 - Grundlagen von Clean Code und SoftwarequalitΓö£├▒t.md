# Clean Code – Block 1: Grundlagen, Prinzipien und Motivation

## 1. Lernziele

Nach diesem Block können die Teilnehmenden:

- Clean Code von lediglich funktionierendem Code unterscheiden.
- Lesbarkeit, Verständlichkeit, Wartbarkeit und Testbarkeit als Qualitätsziele erläutern.
- grundlegende Prinzipien wie KISS, DRY und YAGNI einordnen.
- technische Schulden einschließlich architektureller Schulden erkennen und beschreiben.
- Zweck, Aufbau und Pflege eines Architecture Decision Record (ADR) erklären.
- die Boy Scout Rule und *Clean as you go* anwenden.
- selbstdokumentierenden Code erkennen und von notwendiger Entscheidungsdokumentation unterscheiden.

## 2. Lerninhalte

### 2.1 Was ist Clean Code?

Clean Code erfüllt nicht nur funktionale Anforderungen, sondern ist verständlich, gut strukturiert, wartbar und überprüfbar. Wichtige Eigenschaften sind Lesbarkeit, Einfachheit, geringe unnötige Kopplung und Testbarkeit.

Die Qualität einer Software entsteht nicht allein in einzelnen Quellcodedateien. Auch Modulgrenzen, Schnittstellen, Architekturentscheidungen, Tests und die Dokumentation der wesentlichen Entscheidungen tragen dazu bei, dass ein System langfristig verstanden und weiterentwickelt werden kann. **Ein ADR ersetzt keinen sauberen Code; es erklärt, warum die Architektur so gestaltet wurde.**

### 2.2 Selbstdokumentierender Code

**Selbstdokumentierender Code** macht seine fachliche Absicht und wesentliche Funktionsweise durch sprechende Namen, kleine überschaubare Funktionen, klare Verantwortlichkeiten und eine nachvollziehbare Struktur erkennbar. Eine zusätzliche Beschreibung jedes Verarbeitungsschritts wird dadurch weitgehend überflüssig.

Das bedeutet **nicht**, dass jede Dokumentation entfallen kann: Fachliche Rahmenbedingungen, nicht offensichtliche Gründe für Entscheidungen, Schnittstellenverträge und insbesondere Architekturentscheidungen (ADRs) müssen gegebenenfalls ausdrücklich dokumentiert werden.

**Vergleich im Schulungsprojekt:** Die Variante `dirty` enthält eine `doc.md`, die den schwer verständlichen Programmablauf erklärt. In `clean` soll die Absicht aus dem Quellcode selbst hervorgehen. Die Teilnehmenden vergleichen, welche Aussagen der `doc.md` durch bessere Namen und Struktur entbehrlich werden und welche Informationen unabhängig vom Code erhalten bleiben sollten.

### 2.3 Warum ist Clean Code wichtig?

- Wartungs- und Änderungsaufwand begrenzen
- Fehlersuche und Einarbeitung erleichtern
- Änderungen sicherer und besser testbar machen
- kurzfristige Entwicklungsgeschwindigkeit gegen langfristige Kosten abwägen

### 2.4 Grundprinzipien

| Prinzip | Kernaussage |
| --- | --- |
| KISS – Keep It Simple | Die einfachste angemessene Lösung bevorzugen. |
| DRY – Don't Repeat Yourself | Wissensduplikation vermeiden, nicht jede ähnliche Codezeile abstrahieren. |
| YAGNI – You Aren't Gonna Need It | Keine spekulative Funktionalität auf Vorrat bauen. |
| Separation of Concerns | Unterschiedliche Verantwortlichkeiten trennen. |
| Principle of Least Surprise | Erwartbares Verhalten und verständliche Schnittstellen anstreben. |

Diese Prinzipien sind Leitlinien, keine mechanisch anzuwendenden Regeln. Sie können in konkreten Situationen miteinander in Spannung stehen.

### 2.5 Technical Debt und Architekturentscheidungen

Technische Schulden sind zukünftiger Mehraufwand, der aus technischen Entscheidungen oder unterlassenen Verbesserungen entsteht. Sie können im Quellcode, in Tests, in der Infrastruktur oder in der Architektur liegen.

- **Codebezogene Schulden:** beispielsweise schwer verständliche Funktionen oder unnötige Abhängigkeiten.
- **Architekturelle Schulden:** beispielsweise unpassende Modulgrenzen oder starke Kopplung, die spätere Änderungen verteuern.
- **Bewusste Schulden:** Ein Team akzeptiert einen bekannten Nachteil aus nachvollziehbaren Gründen, etwa wegen eines engen Liefertermins.
- **Unbeabsichtigte Schulden:** Folgen einer Entscheidung werden erst später sichtbar.

**Wichtig:** Nicht jede Architekturentscheidung mit Nachteilen ist eine technische Schuld. Architektur erfordert immer Kompromisse. Schulden entstehen insbesondere dann, wenn eine Entscheidung unter veränderten Bedingungen zusätzliche Änderungs- oder Betriebskosten verursacht.

**Beispiel:** Eine neue Anwendung startet als Monolith. Das kann die angemessene Lösung sein. Wenn später unklare Modulgrenzen und starke Kopplung Änderungen behindern, entsteht möglicherweise architekturelle technische Schuld. Ein ADR hilft, die ursprünglichen Gründe und Annahmen zu verstehen.

### 2.6 Architecture Decision Records (ADR)

Ein **Architecture Decision Record** dokumentiert eine einzelne wesentliche Architekturentscheidung so, dass sie später nachvollziehbar bleibt. ADRs gehören zur technischen Dokumentation und unterstützen die langfristige Wartbarkeit eines Systems.

**Typische Inhalte eines ADR:**

1. **Titel und Kennung:** Welche Entscheidung wird dokumentiert?
2. **Status:** etwa *Proposed*, *Accepted*, *Deprecated* oder *Superseded*.
3. **Kontext und Problem:** Welche Anforderungen, Rahmenbedingungen und Kräfte wirken auf die Entscheidung?
4. **Entscheidung:** Was wird verbindlich festgelegt?
5. **Alternativen:** Welche realistischen Möglichkeiten wurden geprüft?
6. **Konsequenzen:** Welche positiven und negativen Auswirkungen sowie Risiken sind bekannt?
7. **Bezüge:** Welche anderen ADRs oder Dokumente sind relevant?

**Umgang mit ADRs:**

- Einen ADR pro wesentlicher Entscheidung anlegen; kurz, konkret und verständlich formulieren.
- ADRs möglichst zusammen mit dem Quellcode versionieren, beispielsweise unter `docs/adr/`.
- Entscheidungen im Team diskutieren und den Status sichtbar machen.
- Akzeptierte Entscheidungen als historische Dokumentation erhalten. Bei einer grundlegenden Änderung einen neuen ADR erstellen und den alten als *Superseded* kennzeichnen.
- Bekannte Nachteile und bewusst akzeptierte technische Schulden ausdrücklich festhalten, gegebenenfalls mit Bedingungen für eine Neubewertung.

**Abgrenzung:** Ein ADR dokumentiert eine Entscheidung und ihre Begründung. Es ersetzt weder Architekturdiagramme noch API-Dokumentation, Tests oder den Quellcode selbst.

### 2.7 Boy Scout Rule und Clean as you go

Die **Boy Scout Rule** bedeutet: Hinterlasse den Code möglichst sauberer, als du ihn vorgefunden hast. *Clean as you go* verankert kleine Qualitätsverbesserungen im laufenden Entwicklungsprozess.

- Kleine Verbesserungen bei der Arbeit mit erledigen.
- Beobachtbares Verhalten bei Refactorings erhalten und mit Tests absichern.
- Größere Umbauten bewusst planen, statt sie unkontrolliert in kleine Änderungen einzustreuen.
- Bei relevanten Architekturänderungen auch die ADR-Dokumentation prüfen.

### 2.8 Clean Code als Teamaufgabe

Coding Conventions, Code Reviews, automatisierte Tests, statische Analyse, Refactoring und nachvollziehbare Architekturentscheidungen schaffen gemeinsame Qualitätsstandards. Ein ADR ist dabei kein Selbstzweck, sondern eine Hilfe für künftige Entscheidungen.

## 3. Zentrale Begriffe

| Begriff | Bedeutung |
| --- | --- |
| Clean Code | Verständlicher, wartbarer und überprüfbarer Quellcode im Kontext guter Softwareentwicklung. |
| Selbstdokumentierender Code | Code, dessen Absicht und wesentliche Funktionsweise sich aus Namen und Struktur erschließen. |
| Code Smell | Hinweis auf ein mögliches Qualitätsproblem. |
| Refactoring | Verbesserung der inneren Struktur ohne Änderung des beobachtbaren Verhaltens. |
| Technical Debt | Zusätzlicher zukünftiger Aufwand aufgrund technischer Entscheidungen oder Versäumnisse. |
| Architekturentscheidung | Bewusste Festlegung zur grundlegenden Struktur oder zu wesentlichen technischen Eigenschaften eines Systems. |
| Architectural Technical Debt | Technische Schulden, die aus der Architektur oder ihrer Weiterentwicklung resultieren. |
| ADR | Kurzes, versioniertes Dokument einer wesentlichen Architekturentscheidung mit Kontext und Konsequenzen. |
| Boy Scout Rule | Den bearbeiteten Code nach Möglichkeit etwas sauberer hinterlassen. |
| Clean as you go | Qualitätsverbesserungen fortlaufend in die Entwicklung integrieren. |

## 4. Praktische Anwendung (ca. 20 Minuten)

**Teil A – Codequalität (ca. 10 Minuten):** Einen funktionierenden, aber schwer verständlichen Codeausschnitt analysieren. Fachliche Aufgabe beschreiben, Verständnishürden identifizieren und Verbesserungen priorisieren. Anschließend `dirty/doc.md` mit `clean` vergleichen: Welche Erläuterungen sind durch selbstdokumentierenden Code überflüssig geworden?

**Teil B – Architekturentscheidung (ca. 10 Minuten):** Den Beispiel-ADR `adr-0001-monolith.md` lesen und diskutieren:

- Welche Rahmenbedingungen begründen die Entscheidung?
- Welche Alternativen wurden erwogen?
- Welche Nachteile werden bewusst akzeptiert?
- Wann müsste die Entscheidung überprüft werden?
- Ist ein genannter Nachteil bereits technische Schuld oder zunächst nur ein Trade-off?

## 5. Kernaussagen

Funktional korrekter Code ist nicht automatisch guter Code. Langfristige Wartbarkeit hängt auch von Architektur, Tests und nachvollziehbaren Entscheidungen ab. Technische Schulden können bewusst oder unbeabsichtigt entstehen; ADRs machen die Gründe, Alternativen und Konsequenzen wichtiger Architekturentscheidungen transparent. Selbstdokumentierender Code reduziert erklärende Implementierungsdokumentation, ersetzt aber keine Dokumentation wesentlicher Entscheidungen. Qualität wird kontinuierlich im Team entwickelt.
