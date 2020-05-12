# Beschreibung des Aufbaus des Klassendiagramms

## Semantic tags and rules
+ enthält Sammlung aller Regeln, die das Programm kennt
    + commonRequiredFields: Attribute, die jeder Stil enthalten muss
    + commonOptionalFields: Attribute, die alle Stile enthalten können
    + sortableFields: Attribute nach denen sortiert werden kann
    + styles: Stile der Bib-Elemente (article, book, ...)
    + Style: enthält Name und alle zwingend erforderlichen bzw. möglichen Attribute eines BibTex-Stils
    + Field: jedes Attribut enthält Name und Formatierungsrichtlinie

## Parser
+ steuert Kernfunktionalität des Programms 
+ beinhaltet den Datenpointer zur Regeldatei (semantic tags and rules) 
    + Kontrolle über Bearbeitung der BibTex-Dateien
    + parsed die Bib-Einträge
    + liest Bib-Einträge, überprüft Einhaltung der festgelegten Regeln (semantic tags and rules), parsed positiv überprüfte Einträge in interne Objekte
        + Überprüfung mithilfe von StyleProperties und FieldConstraint (enthalten Regeln)
    + gibt interne Objekte an FileGenerator weiter, um Ausgabdatei zu erzeugen

## BibElement
+ Datenstruktur, die einen valide geparstes Bib-Eintrag beinhaltet
+ Bib-Eintrag wird eingelesen, Einhaltung der semantic tags and rules überprüft, bei Erfolg Speicherung des Eintrags als BibElement in Parser

## Field
+ Datenstruktur, die ein Attribut als key-value-pair speichert

## TranslationTable
+ liest semantic tags and rules ein, parsed die Inhalte und erstellt einen Inhaltsbaum 
+ erstellt aus Regeln StyleProperties und FieldConstraints

## StyleProperties
+ enthält Regeln für einen BibTex-Stils

## FieldConstraint
+ enthält eine Regel für ein Attribut
+ wird für Einhaltung des passenden Datentyps zum Attribut verwendet

## Main
+ steuert Eingabe (Kommandozeilenargumente) und ruft passende Funktionen auf

## FileGenerator
+ bekommt alle validen Elemente und eine Sortierung übergeben und erstellt je nach Unterklasse eine Ausgabedatei
+ Unterklassen steuern Ausgabetyp und überschreiben die write-Methode