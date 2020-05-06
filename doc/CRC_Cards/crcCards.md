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

<p> Sammlung von Regeln und Werten, mit welchen das Programm funktioniert <br><br>

| Klasse: bib_element| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Überprüfung der vorhandenen Attribute mit ihren Werten  | |
| Hinzufügen von Attributen| |
| Bearbeiten/Löschen von Attributen (falls sich jem. verschrieben hat)||

<p> verwaltet die einzelnen Quelleinträge<br><br>

| Klasse: bib_data| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält die Bib Elemente  | bib_element|
| Hinzufügen von Bibelementen| bib_element|

<p> verwaltet alle Elemente<br><br>

| Klasse: output_format| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält Liste der Ausgabeformate  | HTML|
| enthält die Tags  | XML|
| sortiert die Tags  | PDF|

<p> sammelt/verwaltet die Ausgabeformate<br><br>

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

<p> verwaltet die spezifischen Anforderungen an den Aufbau <br><br>

| Klasse: parser| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Verwaltet alle Elemente, Tags, Dateien, etc.| bib_data, translation_table, output_format|

<p>Kernfunktionalität<br>
