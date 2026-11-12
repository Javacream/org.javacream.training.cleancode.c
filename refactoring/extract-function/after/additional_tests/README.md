# Zusätzliche Unit-Tests für Extract Function

Die beiden Testfälle in `test_subtotal.c` prüfen die nach dem Refactoring extrahierte Funktion `subtotal()` **direkt**:

1. **Drei Preise:** `10.0 + 20.0 + 7.5 = 37.5`.
2. **Leere Liste:** Bei `count = 0` ergibt sich `0.0`.

Der ursprüngliche Regressionstest in `../../test.c` bleibt unverändert und prüft weiterhin das Gesamtverhalten über den Variantenadapter.

`subtotal()` ist bewusst `static`. Die zusätzliche Testdatei bindet `../main.c` in dieselbe Übersetzungseinheit ein und benennt dessen `main`-Funktion vorübergehend um. Dadurch sind direkte Tests möglich, **ohne die öffentliche API zu erweitern**. Dieses Vorgehen eignet sich für das kompakte Schulungsbeispiel; in größeren Projekten sind eigene Module und öffentliche Testschnittstellen gegebenenfalls vorzuziehen.

Ausführung im Verzeichnis `refactoring/extract-function/after`:

```sh
make test
```

Der Aufruf führt zuerst die gemeinsamen Regressionstests und anschließend diese beiden zusätzlichen Tests aus.
