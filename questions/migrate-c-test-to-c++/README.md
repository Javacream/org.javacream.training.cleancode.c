# Demo: C-Tests nach C++/GoogleTest migrieren

Ein eigenständiges Beispiel mit einem **unveränderten C-Service** zur Kreisberechnung und zwei Testimplementierungen.

- `src/`: C90-Service mit `area(radius)` und `perimeter(radius)`
- `test/c/`: ursprüngliche C-Tests mit eigener Assertion-Auswertung
- `test/c++/`: dieselben Fälle als C++-Tests mit GoogleTest

Die Tests prüfen Nullradius, bekannte Ergebnisse, gebrochene Radien sowie negative und nicht endliche Eingaben. Ungültige Radien ergeben `-1.0`; für gültige Radien gilt `r >= 0` und der Radius muss endlich sein.

## Voraussetzungen

CMake 3.16+, C90-Compiler, C++17-Compiler, GoogleTest. CMake verwendet eine installierte GoogleTest-Version, andernfalls lädt es GoogleTest über `FetchContent` herunter (Internet erforderlich).

## Bauen und testen

Die folgenden Befehle werden im Verzeichnis `questions/migrate-c-test-to-c++` ausgeführt:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Nur C-Tests: `ctest --test-dir build -R '^circle_c$' --output-on-failure`

Nur C++-Tests: `ctest --test-dir build -R '^circle_cpp$' --output-on-failure`

Der Produktionscode wird **immer als C90** kompiliert. Die C++-Tests binden den unveränderten C-Header mit `extern "C"` ein.

Hinweis: Beide Testsuiten sind hier absichtlich parallel vorhanden, um den Migrationsschritt zu demonstrieren; in einem realen Projekt kann die C-Suite nach erfolgreicher Übernahme entfallen.
