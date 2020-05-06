| Klasse:  translation_table | |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Konvertiert die Bib-Datei | Ausgabeformate|
| Auflistung der Attribute (Kategorien wie Autor, Titel...)  |Bib Elemente|
| Hinzufügen der Attribute  ||
| Überprüfung der vorhandenen Atribite ||
| Enthält Liste mit "Regelwerk" mit Atributzuweisungen für jede Refernzart||
| Input Validierung für Atributswerten (Regeln für Atributwerte) | |
| Test ob Sortierung des Attributs überhaupt möglich| |
<p> Sammlung von Regeln und Werten mit, welchen das Programm funktioniert <br><br>

| Klasse: bib_element| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Überprüfung der vorhandenen Attribute mit ihren Werten  | |
| Hinzufügen von Atributen| |
| Bearbeiten/Löschen von Attributen (falls sich jem. verschrieben hat)||
<p> verwaltet die einzelnen Quelleinträge<br><br>

| Klasse: bib_data| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Entghält die Bib Elemente  | Bib Elemente|
| Hinzufügen von Bibelementen| |
| Bib Elemente ?| |
<p> verwaltet alle Elemente<br><br>

| Klasse: Output_format| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Enthält Liste der Ausgabeformate  | HTML|
| Enthält die Tags  | XML|
| Sortiert die Tags  | PDF|
<p> sammelt/verwaltet die Ausgabeformete<br><br>

| Klasse: Html| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
|  Erzeugten der Ausgabedatein aus den Tags| |

| Klasse: XML| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugten der Ausgabedatein aus den Tags| |

| Klasse: PDF| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Erzeugten der Ausgabedatein aus den Tags| |
<p> verwaltet die spezifischen Anforderungen an den Aufbau <br><br>

| Klasse: Parser| |
| ------------- |:-------------:|
| **Verantwortlichkeiten:** | **Kollaborationen:** |
| Verwaltet alle Elemente, Tags, Datein, etc.| bib_data|
| |translation_table|
| | Output_format|
<p>Kernfunktionalität<br>