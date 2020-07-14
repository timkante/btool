# Candidates Responsibility Collaboration (CRC-Cards)

| Klasse:  Translationtable | |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| konvertiert die Bib-Datei | FileGenerator|
| Auflistung der Attribute (Kategorien wie Autor, Titel...)  | BibElement, Field|
| Hinzufügen der Attribute  | Field |
| Überprüfung der vorhandenen Attribute | Field |
| enthält Liste mit "Regelwerk" mit Attributzuweisungen für jede Referenzart| StyleProperties |
| Input Validierung für Attributswerte (Regeln für Attributwerte) | |
| Test, ob Sortierung des Attributs überhaupt möglich| |

Sammlung von Regeln und Werten, mit welchen das Programm funktioniert

| Klasse: BibElement| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| verwaltet alle Attribute eines BibElements mit den zugehörigen Werten| Field |
| Überprüfung der vorhandenen Attribute mit ihren Werten  | StyleProperties |
| Hinzufügen von Attributen| Field |
| Bearbeiten/Löschen von Attributen (falls sich jem. verschrieben hat)| Field |

verwaltet die einzelnen Quelleinträge

| Klasse: BibData| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält die BibElemente  | BibElement|
| Hinzufügen von BibElementen| BibElement|

verwaltet alle Elemente

| Klasse: FileGenerator| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| enthält Liste der Ausgabeformate  | HTML, XML, PDF|
| enthält die geparsten BibElements  | BibData |
| sortiert die geparsten BibElements  | |

sammelt/verwaltet die Ausgabeformate

| Klasse: HTML| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
|  Erzeugen der Ausgabedateien aus den sortierten und geparsten BibData | FileGenerator |

| Klasse: XML| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugen der Ausgabedateien aus den sortierten und geparsten BibData | FileGenerator |

| Klasse: PDF| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugen der Ausgabedateien aus den sortierten und geparsten BibData | FileGenerator |

verwaltet die spezifischen Anforderungen an den Aufbau

| Klasse: Parser| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Verwaltet alle Elemente, Tags, Dateien, etc.| BibData, Translationtable, FileGenerator , Styleproperties, Field|

Kernfunktionalität

| Klasse: Field | |
| ------------ |:--------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Verwaltet einen Attributnamen und -wert der BibElemente | Parser, BibElement |

speichert die Attributnamen und -werte der BibElemente

| Klasse: Styleproperties | | 
| ----------------------- |:-------------:|
|**Verantwortlichkeiten:** | **Kollaborationen:**|
| verwaltet die erforderlichen und möglichen Attribute eines Stils | Translationtable, Parser |

speichert die Regeln eines Stils
