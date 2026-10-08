# Trainingsumgebung

## Voraussetzungen

- Visual Studio Code
- Docker Engine oder eine Docker-kompatible Container-Laufzeit
- VS-Code-Erweiterung **Dev Containers**

## Start

1. Das Hauptverzeichnis `clean-code-training` in Visual Studio Code öffnen.
2. `Dev Containers: Reopen in Container` ausführen.
3. Eine C-Datei in `original/` oder `clean/` öffnen.
4. Über die Start-Schaltfläche oben rechts im Editor **Debug C/C++ File** wählen, um das Programm im Debugger auszuführen.
5. Alternativ **Run C/C++ File** verwenden und eine eventuell offen gebliebene Debug-Session anschließend manuell beenden.

## Werkzeuge im Container

- GCC
- GDB
- Make
- Valgrind
- cppcheck
- Git

Die C-Programme werden im C90-Modus kompiliert.

## Hinweis zu Run und Debug in VS Code

Bei **Run C/C++ File** wurde in der verwendeten VS-Code-/C/C++-Extension-Umgebung beobachtet,
dass die schwebende Debug-Steuerleiste nach dem regulären Programmende sichtbar bleiben kann.
Ein erneuter Programmstart kann zusätzliche Sessions anzeigen, obwohl das zuvor gestartete
C-Programm bereits beendet wurde.

Die Ursache ist nicht abschließend geklärt. Ein Fehler oder ein spezielles Verhalten
von VS Code beziehungsweise der C/C++-Extension ist möglich.

**Vorgehen im Seminar:** Programme können über **Debug C/C++ File** im Debugger gestartet werden.
Alternativ kann **Run C/C++ File** verwendet werden. Bleibt danach eine Debug-Session sichtbar,
wird sie über die rote **Stop**-Schaltfläche manuell beendet. Eine sichtbare Debug-Leiste
bedeutet nicht zwangsläufig, dass das C-Programm noch läuft.

Für dieses Verhalten sind keine weiteren Konfigurationsänderungen vorgesehen.

## Verzeichnisprinzip

`original/` enthält die Ausgangsversionen.

`clean/` enthält die überarbeiteten Versionen.

Die acht Unterverzeichnisse entsprechen den acht Seminarblöcken und tragen jeweils den Namen des Blocks.
