# Excessive Conditional Compilation – Code Smell in C

## Einordnung

Die übermäßige Verwendung von `#if`, `#ifdef` und `#ifndef` wird als **Excessive Conditional Compilation** bezeichnet. Sie ist ein möglicher **Code Smell** in C-Programmen: Verschiedene Implementierungsvarianten werden durch Präprozessorbedingungen innerhalb derselben Quelltexte verwaltet. Die Folgen können eingeschränkte Lesbarkeit, erschwerte Testbarkeit und hoher Änderungsaufwand sein.

**Nicht jede bedingte Kompilierung ist problematisch.** Include Guards, plattformspezifische Implementierungen oder Embedded-Konfigurationen sind etablierte Anwendungsfälle. Entscheidend sind Umfang, Verschachtelung, Streuung und fachliche Bedeutung der Bedingungen.

## Beispiel: Vermischung von Fachlogik und Konfiguration

```c
int calculate_price(int amount)
{
#ifdef CUSTOMER_A
    int discount = 10;
#elif defined(CUSTOMER_B)
    int discount = 15;
#else
    int discount = 0;
#endif

#ifdef ENABLE_TAX
#ifdef COUNTRY_DE
    amount += amount * 19 / 100;
#else
    amount += amount * 20 / 100;
#endif
#endif

    return amount - discount;
}
```

Der tatsächliche Programmablauf hängt von mehreren Übersetzungsschaltern ab. Der Quelltext zeigt nicht unmittelbar, welche Variante in einer konkreten Binärdatei enthalten ist. Zusätzlich werden Kundenvarianten und Steuerregeln mit der eigentlichen Berechnung vermischt.

Das Beispiel dient der Illustration des Smells; die Rabatt- und Steuerberechnung ist keine fachlich vollständige Preisberechnung.

## Auswirkungen

| Qualitätsmerkmal | Problem |
|---|---|
| Lesbarkeit | Der relevante Kontrollfluss hängt von Präprozessordefinitionen ab. |
| Wartbarkeit | Änderungen müssen in mehreren Varianten nachvollzogen werden. |
| Testbarkeit | Nicht aktive Zweige sind in einem konkreten Build nicht ausführbar. |
| Komplexität | Mehrere unabhängige Schalter erzeugen viele mögliche Kombinationen. |
| Statische Analyse | Viele Werkzeuge untersuchen nur ausgewählte Präprozessor-Konfigurationen. |
| Code Coverage | Die Abdeckung eines Builds belegt keine Abdeckung aller Varianten. |

Bei fünf unabhängigen binären Schaltern existieren theoretisch `2^5 = 32` Kombinationen. Nicht alle Kombinationen müssen zulässig oder sinnvoll sein; dies ist bei der Testplanung zu berücksichtigen.

## Beziehung zu anderen Code Smells

*Excessive Conditional Compilation* ist keine klassische Bezeichnung aus Fowlers ursprünglichem Code-Smell-Katalog. Es gibt jedoch Überschneidungen:

| Code Smell | Bezug |
|---|---|
| Conditional Complexity | Tiefe und umfangreiche Präprozessor-Verzweigungen erschweren das Verständnis. |
| Shotgun Surgery | Eine fachliche Änderung erfordert Anpassungen in zahlreichen verstreuten Varianten. |
| Divergent Change | Eine Funktion enthält plattform-, kunden- und fachabhängige Änderungsgründe. |
| Duplicated Code | Mehrere Varianten enthalten ähnliche oder identische Implementierungen. |

Die häufigsten Probleme entstehen durch die Kombination aus komplexen Bedingungen und über viele Dateien verteilten Konfigurationsentscheidungen.

## Refactoring-Strategien

### 1. Bedingte Kompilierung kapseln

Wenn nur eine plattformabhängige Operation variiert, kann die Präprozessorentscheidung in eine eigene Funktion verschoben werden.

**Vorher:**

```c
void process_order(void)
{
#ifdef WINDOWS
    windows_log("Order started");
#else
    linux_log("Order started");
#endif

    /* Geschaeftslogik */

#ifdef WINDOWS
    windows_log("Order finished");
#else
    linux_log("Order finished");
#endif
}
```

**Nachher:**

```c
void platform_log(const char *message)
{
#ifdef WINDOWS
    windows_log(message);
#else
    linux_log(message);
#endif
}

void process_order(void)
{
    platform_log("Order started");

    /* Geschaeftslogik */

    platform_log("Order finished");
}
```

Die Konfigurationsentscheidung befindet sich nur noch an einer Stelle. Voraussetzung ist, dass `windows_log` beziehungsweise `linux_log` in der jeweiligen Zielumgebung bereitstehen.

### 2. Plattformabhängige Implementierungen in Dateien trennen

Bei größeren Unterschieden empfiehlt sich eine Trennung auf Modulebene:

```text
src/
├── platform.h
├── platform_windows.c
├── platform_linux.c
└── application.c
```

Die gemeinsame Schnittstelle:

```c
/* platform.h */
void platform_log(const char *message);
```

Das Buildsystem wählt die passende Implementierung:

```cmake
if(WIN32)
    target_sources(app PRIVATE src/platform_windows.c)
else()
    target_sources(app PRIVATE src/platform_linux.c)
endif()
```

Die Anwendung verwendet ausschließlich `platform_log()`. Die Auswahl der plattformspezifischen Quelldatei ist damit vom Anwendungscode getrennt. Das `else()` steht hier beispielhaft für die unterstützte Nicht-Windows-Plattform; bei mehreren Plattformen sind explizite Zweige erforderlich.

### 3. Fachliche Varianten zur Laufzeit konfigurieren

Für fachliche Entscheidungen kann eine Laufzeitkonfiguration geeigneter sein.

**Vorher:**

```c
int calculate_discount(void)
{
#ifdef PREMIUM_CUSTOMER
    return 20;
#else
    return 5;
#endif
}
```

**Nachher:**

```c
int calculate_discount(int is_premium)
{
    return is_premium ? 20 : 5;
}
```

Beide Varianten können nun innerhalb desselben Testprogramms geprüft werden. Dies setzt voraus, dass die Entscheidung tatsächlich zur Laufzeit getroffen werden darf. Bei nicht verfügbaren Plattformfunktionen, knappen Embedded-Ressourcen oder Sicherheitsanforderungen kann bedingte Kompilierung weiterhin erforderlich sein.

## Bewertung typischer Einsatzfälle

| Einsatzfall | Einordnung |
|---|---|
| Include Guards in Headern | Standardtechnik, kein Smell |
| Betriebssystemabhängige APIs | Legitimer Anwendungsfall; möglichst gekapselt |
| Unterschiedliche Prozessorarchitekturen | Häufig erforderlich |
| Embedded-Systeme mit begrenzten Ressourcen | Oft zweckmäßig oder notwendig |
| Zentral gesteuertes Debugging oder Tracing | In der Regel vertretbar |
| Kundenspezifische Geschäftsregeln | Kritisch prüfen; Laufzeitkonfiguration erwägen |
| Tief verschachtelte Bedingungen in Fachfunktionen | Deutliches Warnsignal |
| Über viele Module verstreute Feature-Schalter | Deutliches Warnsignal |

## Metriken für bedingte Kompilierung

Die klassische zyklomatische Komplexität bildet Präprozessorvarianten nicht immer vollständig ab. Ergänzend lassen sich folgende Merkmale messen:

| Metrik | Bedeutung |
|---|---|
| Conditional Compilation Directives | Anzahl der Direktiven `#if`, `#ifdef`, `#ifndef` |
| Maximum Preprocessor Nesting Depth | Maximale Verschachtelungstiefe |
| Configuration Symbols | Anzahl unterschiedlicher Konfigurationsmakros |
| Scattering | Anzahl der Dateien oder Stellen, an denen ein Konfigurationsmakro vorkommt |
| Tangling | Anzahl verschiedener Konfigurationsmakros innerhalb einer Funktion oder Datei |

**Scattering** beschreibt die räumliche Verteilung einer Konfigurationsoption; **Tangling** die Vermischung mehrerer Optionen an derselben Stelle. Beide Begriffe sind auch in der Forschung zu Software-Produktlinien gebräuchlich.

Metrikwerte sind Hinweise für die Code-Analyse, keine allgemeingültigen Qualitätsgrenzen. Ein einzelnes `#ifdef` in einem Plattformadapter kann zweckmäßiger sein als eine aufwendige alternative Abstraktion.

## Teststrategie für Varianten

1. **Unterstützte Konfigurationen erfassen:** Konfigurationsmakros, zulässige Kombinationen und Buildprofile dokumentieren.
2. **Varianten gezielt bauen:** Nicht nur den Standard-Build, sondern relevante Konfigurationen kompilieren.
3. **Verhalten je Variante testen:** Gleiche fachliche Verträge soweit möglich mit denselben Testfällen absichern.
4. **Grenzfälle berücksichtigen:** Besonders Kombinationen prüfen, bei denen mehrere Schalter interagieren.
5. **Analyse je Konfiguration bewerten:** Coverage und statische Analyse nicht ungeprüft auf andere Builds übertragen.

## Prüffragen für ein Code-Review

- Beschreiben die Präprozessorbedingungen technische Plattformunterschiede oder fachliche Varianten?
- Sind Konfigurationsentscheidungen zentral gekapselt?
- Wie viele Dateien und Funktionen verwenden dasselbe Konfigurationsmakro?
- Wie tief sind die Bedingungen verschachtelt?
- Werden alle relevanten Konfigurationen gebaut und getestet?
- Lässt sich die Variabilität über Module, Funktionen oder Laufzeitparameter verständlicher darstellen?
- Würde ein Refactoring die Komplexität tatsächlich reduzieren oder lediglich verschieben?

## Zusammenfassung

**Excessive Conditional Compilation** liegt vor, wenn bedingte Präprozessor-Direktiven in einem Ausmaß oder einer Struktur eingesetzt werden, die Verständlichkeit, Testbarkeit oder Änderbarkeit des C-Codes beeinträchtigt. Häufige Gegenmaßnahmen sind die Kapselung von Präprozessorentscheidungen, die Trennung plattformspezifischer Module und – bei geeigneten fachlichen Varianten – die Umstellung auf Laufzeitkonfiguration.

Die Bewertung erfolgt kontextabhängig: Nicht die bloße Anzahl der `#ifdef`-Direktiven ist entscheidend, sondern ihre Wirkung auf die Softwarestruktur und die Zahl der zu beherrschenden Programmvarianten.
