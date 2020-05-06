# Candidates Responsibility Collaboration (CRC-Cards)

| Klasse:  translation_table | |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| konvertiert die Bib-Datei | output_format|
| Auflistung der Attribute (Kategorien wie Autor, Titel...)  |bib_element|
| Hinzufügen der Attribute  ||
| Überprüfung der vorhandenen Attribute ||
| enthält Liste mit "Regelwerk" mit Attributzuweisungen für jede Referenzart||
| Input Validierung für Attributswerte (Regeln für Attributwerte) | |
| Test, ob Sortierung des Attributs überhaupt möglich| |

Sammlung von Regeln und Werten, mit welchen das Programm funktioniert

| Klasse: bib_element| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Überprüfung der vorhandenen Attribute mit ihren Werten  | |
| Hinzufügen von Attributen| |
| Bearbeiten/Löschen von Attributen (falls sich jem. verschrieben hat)||

verwaltet die einzelnen Quelleinträge

| Klasse: bib_data| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält die Bib Elemente  | bib_element|
| Hinzufügen von Bibelementen| bib_element|

verwaltet alle Elemente

| Klasse: output_format| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält Liste der Ausgabeformate  | HTML|
| enthält die Tags  | XML|
| sortiert die Tags  | PDF|

sammelt/verwaltet die Ausgabeformate

| Klasse: Html| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
|  Erzeugen der Ausgabedateien aus den Tags| |

| Klasse: XML| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugen der Ausgabedateien aus den Tags| |

| Klasse: PDF| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugen der Ausgabedateien aus den Tags| |

verwaltet die spezifischen Anforderungen an den Aufbau

| Klasse: parser| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Verwaltet alle Elemente, Tags, Dateien, etc.| bib_data, translation_table, output_format|

Kernfunktionalität
