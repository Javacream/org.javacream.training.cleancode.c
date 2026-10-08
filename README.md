# Clean Code – Trainingsübungen in C90

Dieses Paket enthält die Übungsprogramme für das zweitägige Clean-Code-Seminar.

## Wichtig beim ersten Öffnen

Das Projekt ist für die Arbeit im Dev Container konfiguriert. Nach dem Öffnen des Hauptverzeichnisses auf dem Host daher **direkt `Dev Containers: Reopen in Container` ausführen**, bevor C-Dateien gestartet oder die C/C++-Konfiguration verwendet werden.

Auf einem Windows-Host kann die C/C++-Extension vor dem Wechsel in den Container kurz melden, dass `/usr/bin/gcc` nicht aufgelöst werden kann. Das ist erwartbar: `/usr/bin/gcc` befindet sich im Linux-Dev-Container. Nach dem Öffnen im Container steht der Compiler zur Verfügung und ist für **Run C/C++ File** bzw. **Debug C/C++ File** vorkonfiguriert.

## Struktur

- `dirty/` enthält die jeweilige Ausgangsversion der Übungen.
- `clean/` enthält die zugehörige überarbeitete bzw. saubere Version.
- Die Blockverzeichnisse sind in beiden Bereichen identisch benannt.
- `.devcontainer/` und `.vscode/` gelten für das gesamte Trainingsprojekt.

## Visual Studio Code und Dev Container

Das Hauptverzeichnis `clean-code-training` in Visual Studio Code öffnen und anschließend
`Dev Containers: Reopen in Container` ausführen.

Der Container enthält GCC, GDB, Make, Valgrind und cppcheck. Die Microsoft-C/C++-Extension
ist im Dev Container installiert. GCC (`/usr/bin/gcc`) ist für das Projekt vorkonfiguriert. Die C90-Konformität
wird über die Compileroption `-std=c90` beim Build erzwungen.

## Programme starten

Die gewünschte C-Datei mit `main()` im Editor öffnen. Rechts oben im Editor die
C/C++-Startschaltfläche verwenden:

- **Run C/C++ File** – Programm kompilieren und normal im Terminal ausführen
- **Debug C/C++ File** – Programm kompilieren und mit GDB debuggen

Damit ist für die Übungen weder F5 noch Ctrl+F5 erforderlich.

Beim Kompilieren werden insbesondere folgende Optionen verwendet:

```text
-std=c90 -pedantic -Wall -Wextra -g
```

Bei einer Datei `main.c` wird das ausführbare Linux-Programm `main` im selben Verzeichnis
erzeugt. Dieses Build-Artefakt wird durch `.gitignore` ignoriert.

## Statische Codeanalyse

Über `Tasks: Run Task` → `Static Analysis: cppcheck active file` kann die aktuell geöffnete
Datei mit cppcheck untersucht werden. Dies ist insbesondere für Block 6 vorgesehen.

## Übungen

Die Teilnehmenden arbeiten grundsätzlich mit den Dateien unter `dirty/`.
Die Dateien unter `clean/` dienen als Musterlösung, Vergleichsstand und für
Trainerdemonstrationen.


## Überarbeitete Lernbeispiele

Die acht Blöcke bauen aufeinander auf. Jeweils `dirty` und `clean` vergleichen; Aufgaben und Abgrenzung stehen unter `resources/NN - ... .md`.

- `make` kompiliert die Anwendung.
- `make check` führt in Block 7 (clean) und Block 8 (beide Varianten) Tests aus; in den anderen Blöcken die Anwendung.
- Block 6: `make metrics` erzeugt mit **Lizard und Cppcheck** den Bericht `resources/quality-report-block06.md`. Für alle Blöcke: `python3 analyze.py --output quality-report.md`.
- Block 8: erst Tests ausführen, dann kleine Refactoring-Schritte vornehmen.
- Die Programme verwenden ganzzahlige Beispielwerte und sind nicht für Produktion (Überlaufprüfung, Währung) ausgelegt.

## Qualitätsanalyse

Die Devcontainer-Umgebung enthält Lizard und Cppcheck. `python3 analyze.py` analysiert alle acht Blöcke und erzeugt einen Markdown-Vergleich der Varianten `dirty` und `clean`. Die Messwerte sind Indikatoren, keine abschließende Bewertung der Softwarequalität.

### Devcontainer für die Metrikanalyse

In VS Code **Dev Containers: Rebuild and Reopen in Container** ausführen,
damit die aktualisierte Umgebung mit GCC, GDB, Cppcheck und Lizard gebaut wird.
Lizard wird in `/opt/metrics-venv` installiert; dessen Python liegt im `PATH`.
Über **Terminal → Run Task** stehen die Aufgaben `Metrics: analyze all blocks`,
`Metrics: analyze block 06` und `Metrics: check installed tools` bereit.
Die Analyseberichte werden erst bei Ausführung erzeugt.
