# Block 03 – Namen, Datentypen und Ausdruckskraft

## Musterlösung für die Nachbesprechung

**Quellen:** `blocks/03-namen-datentypen/` im Branch `training`.

**Hinweis für die Lehrperson:** Die Musterlösung beschreibt eine fachlich begründete Referenz, nicht die einzig zulässige Umsetzung. Die Aufgaben werden anhand der tatsächlichen Beispielprogramme besprochen.

## 1. Diagnose von `dirty/main.c`

- `s` kodiert den Versandstatus mit den Werten 0 (angelegt), 1 (verpackt), 2 (versendet). Der Typ `int` allein vermittelt diese Bedeutung nicht.
- `x` bezeichnet den Zahlungsstatus, `y` das Merkmal „ungültige Adresse“. Die Ausdrücke `x == 1` und `y == 0` zwingen zum Nachschlagen.
- `z` ist die nichtnegative Sendungsnummer. Der Name erklärt die Rolle nicht.
- Die Bedingung `s == 2 && x == 1 && y == 0` ist fachlich korrekt, aber wenig ausdrucksstark.

## 2. Musterlösung anhand von `clean/main.c`

| Ausgangscode | Referenzlösung | Gewinn |
|---|---|---|
| `int s`, `s == 2` | `ShipmentStatus status`, `status == SHIPMENT_SENT` | Fachliche Zustände sind benannt |
| `x == 1` | `payment_received` | Positive Aussage statt Zahlvergleich |
| `y == 0` | `address_valid` | Doppelte Verneinung wird vermieden |
| `int z` | `unsigned int shipment_id` | Nichtnegative Identifikation und aussagekräftiger Name |

Der Status wird als `typedef enum { SHIPMENT_CREATED, SHIPMENT_PACKED, SHIPMENT_SENT } ShipmentStatus;` modelliert. Das Eingabeformat bleibt numerisch: zunächst werden `int`-Werte eingelesen und validiert, anschließend erfolgt die Konvertierung. In C90 gibt es keinen standardisierten `bool` aus `<stdbool.h>`; `int` mit 0/1 und klaren Namen ist daher angemessen. **Wichtig:** `enum` erzwingt in C keine vollständige Laufzeitvalidierung; auch `unsigned int` ersetzt keine Prüfung der Eingabe.

## 3. Verhaltensvertrag und Erfolgskriterien

| Aufruf | Erwartete Ausgabe |
|---|---|
| `./app 2 1 0 3` | `Shipment 3: ready` |
| `./app 1 1 0 3` | `Shipment 3: not ready` |
| `./app 2 0 0 3` | `Shipment 3: not ready` |
| `./app 2 1 1 3` | `Shipment 3: not ready` |

Beide Versionen müssen die gleichen Ergebnisse und für ungültige Eingaben den Exitcode 1 sowie die Usage-Meldung liefern. Die Teilnehmenden können mindestens drei Typ- oder Namensentscheidungen begründen und haben **keine** Funktionszerlegung vorgenommen. Die Kommandos sind in `dirty/` und `clean/` getrennt auszuführen.

## 4. Reflexion – Musterantworten

**Wann hilft ein eigener Typ?** Wenn er einen abgeschlossenen fachlichen Wertebereich verständlich macht, etwa die drei Versandstatus. Ein `enum` reduziert magische Zahlen und erleichtert Reviews.

**Wann ist eine Abstraktion überflüssig?** Wenn sie lediglich einen einmaligen Ausdruck versteckt, ohne dessen Bedeutung oder Änderbarkeit zu verbessern.

**Ist `unsigned int` immer besser für IDs?** Nicht zwingend: Er verhindert negative Werte im gespeicherten Typ, macht aber die Eingabeprüfung nicht entbehrlich und kann bei unbedachter Konvertierung unerwartete große Werte erzeugen.

**Warum keine zusätzlichen Funktionen?** Dieser Block fokussiert Namen und Typen. Eine Zerlegung würde das Lernziel mit dem Thema des nächsten Blocks vermischen.
