# Refactoring der Ausgangsanwendung

Die fachlichen Versandregeln und das Textdateiformat bleiben erhalten. Verbesserungen: getrennte Module für Fachlogik, Dateispeicherung und Programmstart; sprechende Namen; benannte Tarifkonstanten; keine globalen Auftragsdaten; explizite Erfolgs-/Fehlerstatuswerte; Eingabevalidierung.

`make test` prüft Versandkosten-Grenzen, doppelte IDs, ungültige Eingaben, Speichern/Laden und Stornieren. `make clean` entfernt ausschließlich das Programm, **nicht** die Auftragsdaten.

Bewusste Abweichung gegenüber `original`: Fehlerhafte Datensätze führen zu einem Lesefehler, statt stillschweigend übersprungen zu werden. Diese Verschärfung der Fehlerbehandlung ist keine reine verhaltenserhaltende Refaktorierung und muss im Review gesondert diskutiert werden. Fehlende Datei wird als leerer Datenbestand interpretiert, andere Öffnungsfehler nicht.

ADR-0002 für Textdateien bleibt hier gültig. Die Persistenztechnologie wird in dieser Phase nicht ausgetauscht. Ein vollständiger Nachweis identischen Verhaltens für alle Fehlerszenarien liegt noch nicht vor.
