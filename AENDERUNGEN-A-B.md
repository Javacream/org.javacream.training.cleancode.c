# Umgesetzte Review-Maßnahmen A und B

- A1/A2: C90-Einstellungen vereinheitlicht; Block 03 verwendet keine C99-Bibliothek mehr; Refactoring-Anleitungen auf C90.
- A3: Optionale Detailausgabe in Block 04 erhalten.
- A4: Block 07 trennt reines Refactoring von neuer Eingabevalidierung; Tests prüfen auch ungewöhnliche Eingaben.
- A5: Sentinel-Kollision und eigener Vertragstest für die neue API.
- A6: Make ist Standard-Build in VS Code; Lizard-Check nutzt den Befehl im PATH.
- B1: Zuordnungsmatrix auf oberster Ebene.
- B2/B7: Lernziele, Verhaltensverträge, Übungen und Erfolgskriterien in den Dokumentationen.
- B3/B4/B5: Ergänzte Verhaltenstests und spezifische Vertragstests für Kontextunabhängigkeit und Cleanup-Fehlerpfade.
- B6: Dritte Variante von Block 06 samt Vergleichstest (`make compare`).

Hinweis: Vertragstests für die neue Schnittstelle sind bewusst nur in `after` vorhanden. Die gemeinsame `test.c` bleibt für beide Varianten erhalten.
