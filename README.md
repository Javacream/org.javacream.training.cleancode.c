# Clean Code – Trainingsübungen in C90

Dieses Paket enthält die Übungsprogramme für das zweitägige Clean-Code-Seminar.

## Wichtig beim ersten Öffnen

Das Projekt ist für die Arbeit im Dev Container konfiguriert. Nach dem Öffnen des Hauptverzeichnisses auf dem Host daher **direkt `Dev Containers: Reopen in Container` ausführen**, bevor C-Dateien gestartet oder die C/C++-Konfiguration verwendet werden.

Auf einem Windows-Host kann die C/C++-Extension vor dem Wechsel in den Container kurz melden, dass `/usr/bin/gcc` nicht aufgelöst werden kann. Das ist erwartbar: `/usr/bin/gcc` befindet sich im Linux-Dev-Container. Nach dem Öffnen im Container steht der Compiler zur Verfügung und ist für **Run C/C++ File** bzw. **Debug C/C++ File** vorkonfiguriert.

## Struktur

- `original/` enthält die jeweilige Ausgangsversion der Übungen.
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

Die Teilnehmenden arbeiten grundsätzlich mit den Dateien unter `original/`.
Die Dateien unter `clean/` dienen als Musterlösung, Vergleichsstand und für
Trainerdemonstrationen.
