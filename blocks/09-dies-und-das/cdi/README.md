# Context und Dependency Injection in C – Handout und Beispiel

## Lernziele

Dieses Beispiel zeigt, wie Zustand und technische Abhängigkeiten in C90 explizit modelliert werden. Der Schwerpunkt liegt auf **Testbarkeit durch Dependency Injection** sowie auf der Unterscheidung von **Dummy**, **Stub** und **Mock** als Test Doubles.

Nach der Bearbeitung lassen sich globale Zustände und versteckte Abhängigkeiten identifizieren, durch einen Context und injizierte Funktionen ersetzen und ohne produktive Infrastruktur testen.

## 1. Context: Zustand explizit übergeben

Eine globale Variable ist für alle Aufrufer derselben Programminstanz gemeinsam sichtbar:

```c
static unsigned request_count;

void process_request(void)
{
    ++request_count;
}
```

Die Funktion besitzt eine versteckte Zustandsabhängigkeit. Tests können sich gegenseitig beeinflussen; unabhängige Instanzen sind nicht ohne Weiteres möglich.

Ein Context macht den Zustand explizit:

```c
typedef struct {
    unsigned request_count;
} RequestContext;

void process_request(RequestContext *ctx)
{
    ++ctx->request_count;
}
```

Vorteile sind nachvollziehbare Zuständigkeiten, definierte Initialisierung, unabhängige Instanzen und bessere Testisolation. Ein Context ist jedoch **nicht automatisch threadsicher**. Gemeinsame Nutzung zwischen Threads erfordert geeignete Synchronisation.

## 2. Dependency Injection: Abhängigkeiten von außen bereitstellen

Dependency Injection (DI) bedeutet, dass eine Komponente eine benötigte Funktion oder Ressource nicht selbst auswählt oder erzeugt. Stattdessen wird die Abhängigkeit bei der Initialisierung oder beim Aufruf übergeben.

In C lässt sich DI ohne Framework realisieren, beispielsweise mit **Funktionszeiger und `void *`-Kontext**:

```c
typedef int (*SaveFunction)(void *user_data, int order_id, int amount);

typedef struct {
    SaveFunction save;
    void *user_data;
} StorageDependency;
```

Die Signatur definiert einen Vertrag: Die Funktion erhält eine Auftragsnummer und einen Betrag und liefert einen Erfolgsstatus. `user_data` ist ein vom Aufrufer bereitgestellter Kontext, den die konkrete Implementierung interpretieren darf.

Diese Konstruktion ist kein DI-Container und kein Service Locator. Die konkrete Abhängigkeit wird explizit übergeben.

## 3. Kombination von Context und DI

Die Demo verwendet einen ApplicationContext:

```c
typedef struct {
    unsigned requests;
    StorageDependency storage;
} ApplicationContext;
```

Damit sind **Zustand** (`requests`) und **technische Abhängigkeit** (`storage`) in einer Instanz zusammengefasst.

Die Initialisierung prüft, ob ein gültiger Context und eine Speicherfunktion vorhanden sind. `process_order()` prüft seine Eingaben, erhöht bei einem gültigen Speicherversuch den Zähler und ruft die injizierte Funktion auf:

```c
int process_order(ApplicationContext *ctx, int order_id, int amount)
{
    if (ctx == 0 || ctx->storage.save == 0 || order_id <= 0 || amount < 0) {
        return 0;
    }
    ++ctx->requests;
    return ctx->storage.save(ctx->storage.user_data, order_id, amount) != 0;
}
```

**Vertrag:** Eine gültige Auftragsnummer ist positiv, ein Betrag nicht negativ. `requests` zählt gültige Speicher**versuche**, auch wenn die Speicherung fehlschlägt. Ungültige Eingaben lösen keinen Speicheraufruf aus.

Die Anwendung in `src/main.c` injiziert `console_save()`. Diese Implementierung schreibt die Auftragsdaten auf die Konsole. Ein realer Adapter könnte stattdessen Dateien, eine Datenbank oder ein externes System verwenden.

## 4. Schwerpunkt: Testen mit Dependency Injection

### Warum verbessert DI die Testbarkeit?

Ohne DI ruft die Geschäftslogik eine fest verdrahtete technische Funktion auf. Tests benötigen dann möglicherweise eine Datei, Datenbank oder Netzwerkverbindung. Fehlerfälle sind schwer gezielt auszulösen und Tests können langsam oder instabil werden.

Mit DI ersetzt ein Test ausschließlich die technische Abhängigkeit. **Der produktive Code in `application.c` bleibt unverändert.** Die Tests können den Erfolg, Fehler und konkrete Aufrufe der Speicherfunktion kontrollieren.

### Testtreiber und Test Doubles

Ein **Testtreiber** ruft die zu testende Komponente auf, legt Eingaben fest und prüft Ergebnisse. In dieser Demo übernimmt `test/test_application.c` diese Aufgabe.

Ein **Test Double** ersetzt dagegen eine echte Abhängigkeit der getesteten Komponente. Dummy und Mock sind unterschiedliche Arten solcher Ersatzobjekte. Die Begriffe sollten nicht gleichgesetzt werden:

| Begriff | Zweck | Verhalten im Beispiel |
|---|---|---|
| **Dummy** | Wird lediglich übergeben; sein Inhalt ist für den Test irrelevant | `DummyStorageContext` ist ein Platzhalter für `user_data` |
| **Stub** | Liefert vordefinierte Antworten | `successful_stub()` liefert immer Erfolg |
| **Mock** | Zeichnet Interaktionen auf oder prüft erwartete Aufrufe | `MockStorage` protokolliert Aufrufzahl und Parameter |
| **Fake** | Enthält eine vereinfachte, funktionsfähige Implementierung | Ein In-Memory-Speicher wäre ein typisches Beispiel; hier nicht implementiert |

**Begriffliche Präzisierung:** Eine aufgerufene Funktion, die immer Erfolg liefert, ist ein **Stub**, nicht allein deshalb ein Dummy, weil sie keine Daten speichert. Der Dummy in der Demo ist das ungenutzte Kontextobjekt. Ein Mock wird hier manuell implementiert; ein Mocking-Framework ist nicht notwendig.

### 4.1 Test mit Dummy und Stub

```c
typedef struct {
    int unused;
} DummyStorageContext;

static int successful_stub(void *user_data, int order_id, int amount)
{
    (void)user_data;
    (void)order_id;
    (void)amount;
    return 1;
}
```

Der Test injiziert den Stub als `save` und übergibt einen Dummy als `user_data`. Der Stub ignoriert sämtliche Parameter. Damit kann isoliert geprüft werden, ob ein gültiger Auftrag erfolgreich verarbeitet wird und der Zähler steigt.

**Grenze:** Der Stub erkennt nicht, ob die richtigen Auftragsdaten übergeben wurden. Dafür ist ein Mock sinnvoll.

### 4.2 Test mit Mock

```c
typedef struct {
    unsigned calls;
    int last_order_id;
    int last_amount;
    int result;
} MockStorage;

static int mock_save(void *user_data, int order_id, int amount)
{
    MockStorage *mock = (MockStorage *)user_data;
    ++mock->calls;
    mock->last_order_id = order_id;
    mock->last_amount = amount;
    return mock->result;
}
```

Der Test kann nach dem Aufruf feststellen, **ob**, **wie oft** und **mit welchen Argumenten** gespeichert wurde:

```c
CHECK(process_order(&app, 17, 250) == 1);
CHECK(mock.calls == 1U);
CHECK(mock.last_order_id == 17);
CHECK(mock.last_amount == 250);
```

Der Mock lässt sich auch so konfigurieren, dass die Speicherung fehlschlägt (`result = 0`). Dadurch kann der Fehlerpfad ohne echte Infrastruktur geprüft werden.

### 4.3 Testfälle der Demo

| Test | Prüfziel |
|---|---|
| `test_with_dummy_and_stub` | Erfolgreicher Ablauf und Zählerstand ohne Infrastruktur |
| `test_mock_verifies_interaction` | Aufrufzahl und übergebene Argumente |
| `test_mock_failure_and_invalid_input` | Speicherfehler und ausbleibende Aufrufe bei ungültigen Eingaben |
| `test_separate_contexts_and_invalid_dependency` | Unabhängige Context-Instanzen und Validierung der Abhängigkeit |

Die Testprüfungen verwenden ein kleines `CHECK`-Makro. Im Unterschied zu `assert()` werden diese Prüfungen nicht durch `NDEBUG` deaktiviert.

### 4.4 Grenzen der Tests

Ein Mock beweist, dass eine Abhängigkeit **wie erwartet aufgerufen** wurde, nicht dass eine echte Datei oder Datenbank korrekt arbeitet. Für produktive Systeme sind daher zusätzlich Integrations- und gegebenenfalls Systemtests mit dem realen Adapter erforderlich.

Tests sollten sich auf relevante Interaktionen beschränken. Übermäßig detaillierte Mock-Erwartungen können Refactorings erschweren, obwohl das fachliche Verhalten unverändert bleibt.

## 5. Code Smells und Architekturfolgen

| Problem | Mögliche Verbesserung |
|---|---|
| Global State | Expliziter, instanzbezogener Context |
| Hidden Dependencies | Abhängigkeit in Initialisierung oder Funktionssignatur |
| Tight Coupling | Austauschbare Implementierungen über Funktionszeiger |
| Hard to Test Code | Isolierte Tests mit Test Doubles |
| Unkontrollierte Lebensdauer | Dokumentierte Ownership und Initialisierung |

Nicht alle Begriffe der Tabelle sind klassische Code Smells aus Fowlers Katalog; einige beschreiben allgemeine Entwurfsprobleme.

## 6. Risiken und Gegenmaßnahmen

**God Context:** Ein Context, der alle Zustände und Dienste der Anwendung enthält, wird selbst zur schwer wartbaren Abhängigkeit. Fachlich zusammengehörige Kontexte sind vorzuziehen.

**Unklare Ownership:** Bei `void *user_data` ist zu dokumentieren, wer den Speicher besitzt und wie lange er gültig bleibt. In dieser Demo werden die Testkontexte auf dem Stack angelegt und nur innerhalb ihrer Lebensdauer verwendet; `ApplicationContext` gibt `user_data` nicht frei.

**Ungültige Funktionszeiger:** Die Initialisierung prüft `storage.save` auf Null. Nach der Initialisierung darf die Abhängigkeit nicht unkontrolliert verändert werden.

**Übermäßige Indirektion:** Nicht jede Hilfsfunktion benötigt DI. Die Technik ist besonders sinnvoll an technischen Grenzen, bei austauschbaren Implementierungen und für gezielt testbare Fehlerpfade.

**Nebenläufigkeit:** Der Zähler `requests` wird ohne Synchronisation verändert. Ein gemeinsam verwendeter Context ist in dieser Form nicht für parallele Schreibzugriffe geeignet.

## 7. Dateien und Ausführung

```text
cdi/
├── README.md
├── Makefile
├── src/
│   ├── application.h
│   ├── application.c
│   ├── console_storage.c
│   └── main.c
└── test/
    └── test_application.c
```

Im Verzeichnis `blocks/09-dies-und-das/cdi`:

```sh
make
make run
make test
make clean
```

Der Build verwendet C90 (`-std=c90 -pedantic`) mit Warnungen als Fehler. Für `make` und den C-Compiler ist eine geeignete lokale Entwicklungsumgebung erforderlich.

## 8. Fragen zur Nachbesprechung

1. Welche Abhängigkeit wird injiziert und welche Daten gehören zum Context?
2. Warum genügt ein Stub zur Ergebnisprüfung, aber nicht zur Kontrolle der übergebenen Argumente?
3. Worin unterscheiden sich Dummy, Stub, Mock und Fake?
4. Was lässt sich mit einem Mock nicht über die reale Speicherimplementierung aussagen?
5. Wie würde sich das Design bei mehreren Speicher-Backends, bei dynamischer Allokation oder bei mehreren Threads verändern?
6. Ab welchem Punkt würde ein Context zum God Context?

## Zusammenfassung

**Context** macht Zustand und Instanzgrenzen sichtbar. **Dependency Injection** entkoppelt fachliche Verarbeitung von technischen Implementierungen. Der wichtigste praktische Nutzen liegt häufig in der **Testbarkeit**: Stubs steuern Antworten, Mocks machen Interaktionen prüfbar, Dummies erfüllen ausschließlich Parameteranforderungen. Die Architektur bleibt C90-konform und benötigt weder einen DI-Container noch ein Mocking-Framework.
