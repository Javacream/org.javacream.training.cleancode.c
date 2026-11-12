# Best Practices: C-Tests nach C++/GoogleTest migrieren

## Ziel und Geltungsbereich

**Nur die Tests werden migriert.** Der C-Service bleibt in C geschrieben und wird weiterhin mit dem C-Compiler übersetzt. C++ und GoogleTest werden ausschließlich für den Testcode verwendet.

Diese Demo enthält die identischen fachlichen Kreisberechnungsfälle in `test/c/` und `test/c++/`. Die öffentliche Schnittstelle lautet `area(double radius)` und `perimeter(double radius)`; ein ungültiger Radius liefert `-1.0`.

## Empfohlener Migrationspfad

1. **Ausgangszustand sichern:** Vorhandene C-Tests ausführen, Ergebnisse und Sonderfälle dokumentieren.
2. **C-Build unverändert lassen:** `circle.c` bleibt eine C-Übersetzungseinheit; den C-Standard ausdrücklich festlegen.
3. **GoogleTest einführen:** C++-Testtarget getrennt erstellen und mit derselben C-Bibliothek verlinken.
4. **Testfälle 1:1 übertragen:** Gleiche Eingaben, erwartete Ergebnisse, Toleranzen und Fehlerfälle. Noch keine fachlichen Änderungen.
5. **Beide Testsuiten parallel ausführen:** Abweichungen untersuchen, nicht durch geänderte Erwartungen „reparieren“.
6. **Tests optional modernisieren:** Erst danach Fixtures, parametrisierte Tests und Hilfsfunktionen einführen.
7. **C-Tests kontrolliert ablösen:** Erst nach erfolgreichem Vergleich und CI-Integration entfernen, sofern keine anderen Anforderungen dagegen sprechen.

## Do's and Don'ts

| Do | Don't | Warum? |
|---|---|---|
| C-Dateien mit einem **C-Compiler** bauen. | `.c`-Dateien einfach als C++ übersetzen. | C und C++ unterscheiden sich bei Typregeln, Schlüsselwörtern und Sprachsemantik. |
| C-Header in C++ mit `extern "C" { #include "..." }` einbinden (als mehrzeiligen Block). | C-Symbole ohne C-Linkage deklarieren. | Sonst drohen Linkerfehler durch C++ Name Mangling. |
| Falls möglich C-Header selbst mit `#ifdef __cplusplus` absichern. | Header nur für Tests mit unkontrollierten Sonderfällen versehen. | Die öffentliche Schnittstelle soll klar und für beide Sprachen nutzbar bleiben. |
| Fachliche Testfälle und Toleranzen unverändert übertragen. | Testmigration mit Verhaltensänderungen vermischen. | Nur so lässt sich eine Abweichung eindeutig zuordnen. |
| `EXPECT_EQ` für exakt vergleichbare Werte und `EXPECT_NEAR` für Fließkommazahlen verwenden. | Berechnete `double`-Werte grundsätzlich mit exakter Gleichheit vergleichen. | Rundungsfehler können ansonsten fragile Tests erzeugen. |
| Bei Fehler-Sentinels den exakten Vertrag prüfen, hier `-1.0`. | Negative Radien stillschweigend als `0` behandeln oder Erwartungen ändern. | Fehlerfälle gehören zum beobachtbaren Verhalten. |
| Ungültige Werte, Grenzwerte und normale Fälle testen. | Nur einen positiven Standardfall prüfen. | Validierung ist ein wesentlicher Teil der Schnittstelle. |
| Globale C-Zustände zwischen Tests zurücksetzen, sofern vorhanden. | Auf eine zufällige Testreihenfolge vertrauen. | GoogleTest kann mehrere Tests in einem Prozess ausführen. |
| C-Objekte und C++-Testcode über eine definierte API verbinden. | `static`-Funktionen durch Einbinden von `.c`-Dateien testbar machen. | Das umgeht Kapselung und kann doppelte Definitionen erzeugen. |
| Speicher-Ownership über die Sprachgrenze dokumentieren. | `malloc`-Speicher mit `delete` oder `new`-Speicher mit `free` freigeben. | Allokations- und Freigabemechanismen dürfen nicht vermischt werden. |
| GoogleTest in CMake reproduzierbar versionieren. | Unkontrolliert die jeweils neueste Framework-Version beziehen. | Reproduzierbare Builds erleichtern CI und Fehleranalyse. |
| C- und C++-Tests zunächst getrennt benennen. | Unterschiedliche Testprogramme mit demselben CTest-Namen registrieren. | Selektives Ausführen und Fehlersuche werden sonst erschwert. |

## Typische Fallstricke

### 1. C-Linkage und Header

Die bestehende C-Deklaration wird in der C++-Testdatei mit C-Linkage eingebunden:

```cpp
#include <gtest/gtest.h>

extern "C" {
#include "circle.h"
}
```

**Achtung:** Dieses Muster eignet sich für einfache C-Header wie in dieser Demo. Ein komplexer C-Header, der selbst C++-Header einbindet oder C++-Konstrukte enthält, sollte besser intern über `#ifdef __cplusplus` abgesichert werden. C++-Standardbibliotheksheader gehören nicht in einen `extern "C"`-Block.

### 2. C- und C++-Compiler getrennt konfigurieren

```cmake
project(circle_test_migration LANGUAGES C CXX)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

Die C-Bibliothek wird mit `add_library(circle STATIC src/circle.c)` gebaut. Der C++-Testlink bindet diese Bibliothek und `GTest::gtest_main` ein. Auf manchen Unix-Systemen wird außerdem `libm` benötigt.

### 3. Assertions: Semantik und Diagnose

| C-Test | GoogleTest | Hinweis |
|---|---|---|
| `assert(actual == expected)` | `EXPECT_EQ(expected, actual)` | Exakte Vergleiche, etwa für Fehlercodes |
| `fabs(actual - expected) <= eps` | `EXPECT_NEAR(expected, actual, eps)` | Absolute Toleranz; für große Werte ggf. relative Toleranz ergänzen |
| Eigene Fehlermeldung + Rückgabecode | `EXPECT_*` | Test läuft nach einem nichtfatalen Fehlschlag weiter |
| Sofortiger Testabbruch | `ASSERT_*` | Bricht nur den aktuellen Test bzw. die aktuelle Testfunktion ab |

**Wichtig:** `assert()` kann mit `NDEBUG` deaktiviert sein. Eine selbst geschriebene C-Testprüfung wie in dieser Demo ist davon nicht betroffen. `EXPECT_NEAR` prüft keine relativen Abweichungen; die Toleranz muss zum Wertebereich passen.

### 4. Fehlerwerte und Sonderfälle

In dieser Demo gilt `radius >= 0` **und** der Radius muss endlich sein. Negative Werte, NaN und positive Unendlichkeit führen zu `-1.0`. Das ist eine bewusst festgelegte **API-Konvention**, keine allgemeine C-Regel.

Ein Sentinel wie `-1.0` ist für Flächen und Umfänge eindeutig, weil gültige Ergebnisse nicht negativ sind. Bei anderen APIs kann ein Statuscode mit Ausgabeparameter robuster sein. **Eine solche API-Änderung gehört aber nicht in die reine Testmigration.**

### 5. GoogleTest-Abhängigkeit

Das CMake-Projekt versucht zunächst `find_package(GTest QUIET)`. Falls GoogleTest nicht installiert ist, verwendet es `FetchContent` mit einer festgelegten Version. Ein erstmaliger Build benötigt dann Internetzugang. Für Offline- oder Unternehmensumgebungen GoogleTest vorinstallieren beziehungsweise über den Paket- oder Dependency-Manager bereitstellen.

### 6. CTest und GoogleTest unterscheiden

- **GoogleTest** stellt Assertions, Testfälle und Testausführung innerhalb des C++-Programms bereit.
- **CTest** startet registrierte Testprogramme und sammelt deren Exitstatus.
- Diese Demo registriert das gesamte C++-GoogleTest-Programm als **einen CTest-Test** (`circle_cpp`). Für die Registrierung einzelner GoogleTest-Fälle kann später `gtest_discover_tests()` verwendet werden.

### 7. C90 und C++17 nicht vermischen

Die Produktionsdatei verwendet C90-konforme Syntax. Testcode darf C++17 nutzen. Dennoch sollten C-Header nur Konstrukte enthalten, die beide Compiler verstehen. Funktionen, die in C als `static` definiert sind, bleiben intern und sind aus den C++-Tests nicht direkt verlinkbar.

## Checkliste vor dem Entfernen der C-Tests

- [ ] Der C-Service wird weiterhin als C kompiliert.
- [ ] Alle ursprünglichen Testfälle wurden fachlich identisch übernommen.
- [ ] Grenzwerte, ungültige Eingaben und Fließkommatoleranzen stimmen überein.
- [ ] Die C++-Tests verwenden die öffentliche C-Schnittstelle.
- [ ] Die Tests sind unabhängig von ihrer Ausführungsreihenfolge.
- [ ] `ctest --output-on-failure` läuft lokal und in CI erfolgreich.
- [ ] Die GoogleTest-Abhängigkeit ist reproduzierbar verfügbar.
- [ ] Keine Änderung am Produktionsverhalten wurde als Teil der Testmigration eingeführt.

## Befehle für diese Demo

```sh
cmake -S demo -B demo/build
cmake --build demo/build
ctest --test-dir demo/build --output-on-failure

# Nur ursprüngliche C-Tests
ctest --test-dir demo/build -R '^circle_c$' --output-on-failure

# Nur migrierte GoogleTest-Tests
ctest --test-dir demo/build -R '^circle_cpp$' --output-on-failure
```

**Fazit:** Eine gute Testmigration verändert die Testinfrastruktur, **nicht den fachlichen Testvertrag und nicht den C-Produktionscode**.
