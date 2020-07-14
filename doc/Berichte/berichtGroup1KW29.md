# 11 Bericht vom 15.07.2020
  
## 11.1  Was ist seit der letzten Woche passiert

+ Besprechung zur Endpräsentation (Bestandteile der Abgabe.pdf)
  + Besprechung des Bearbeitungsfortschritts (Layout der SnowCards anpassen)
    + neue Idee: Inhaltsverzeichnis und Übersicht zu allen Bestandteilen der Abgabe in README
  + Terminvorschlag für Endpräsentation:
    + Terminvorschlag wurde angenommen
+ Weiterführung der Implementierungen der Klassen
  + Tim: TranslationTable
    + Status: TranslationTable wurde weiter implementiert.
  + Saskia, Valeri, Rashid:  FileGenerator, XML
    + Status: FileGenerator wurde weiter implementiert, Ausgabeformat XML wurde implementiert. 
  + Kevin, Tom, Martin: Parser
    + Status: Parser wurde weiter implementiert. Bib - Dateien werden eingelesen und anhand des übergebenen Stils in Objekte geparst. Dabei wird darauf geachtet, dass alle benötigten Felder des Stils in dem Eintrag der Bib-Datei gesetzt sind. Es wurde sich darauf geeinigt, dass bei jeder Abweichung (also die Bib-Datei kann nicht geparst werden) der Abbruch des Parsing-Vorgangs erfolgt. Der Parser erkennt in Texten automatisch Umlaute (bsp. Bib-Umlaut für ein ä: `{/"a}`) und ersetzt diese durch das entsprechende Pendant.
+ Implementierung von Kommentaren im Code mittels Doxygen
+ Weiterführung der Bearbeitung der Bestandteile für die Abgabe:
    + Erstellung des Sequenz-, Zustands- und Use-Case-Diagramms

## 11.2 Was waren die Herausforderungen und Probleme? Wie wurden sie gelöst

+ vollständig korrekte Implementierung der Klassen benötigt Zeit
  + zusätzlich zum Code müssen Tests geschrieben werden, welche ebenfalls relativ viel Zeit benötigen
  + Anfertigen von Kommentaren ebenfalls zeitaufwändig
+ Ausfall des montägigen Meetings, weil mehr Zeit für Bearbeitung der neuen Aufgaben und Programmierung benötigt wurde.
  + dadurch fehlende Kommunikation zwischen den Programmiergruppen
  + dadurch mehr Zeitaufwand für Koordination und Absprache in wöchentlichem Meeting (Update Bearbeitungsstand, ...)

## 11.3 Was lief gut? Was lief nicht gut

### 11.3.1 Was lief gut

+ Bearbeitung der Aufgaben für Abgabe in Teilgruppen
+ Gruppenübergreifende Hilfestellung bei der Implementierung der Klassen
+ Umsetzung der Quellcodedokumentation in Netlify

### 11.3.2 Was lief nicht gut

+ Unerwartet hoher zeitlicher Aufwand, weil bereits erstellte Aufgaben (siehe Meilenstein 1 bis 4) wiederholt und ergänzt werden müssen
+ Weniger Bearbeitungszeit für Aufgaben aufgrund bevorstehender Klausuren vorhanden

## 11.4 Was haben Sie gelernt? Was würden Sie beim nächsten Mal anders machen

### 11.4.1 Was haben Sie gelernt

+ Erweiterung des Verstädnisses Regulärer Ausdrücke (für Parser nützlich)
+ Besseres Verständnis durch Ergänzung und Wiederholung der ersten Meilensteine, bzw. neue Einarbeitung in Use-Case-Diagramme  (verschiedene Diagramme)
+ besseres Verständnis für Dokumentation des Quellcodes durch Doxygen, Netlify

### 11.4.2 Was würden Sie beim nächsten Mal anders machen

+ besseres Zeitmangement: viele Aufgaben parallel bis zum Abgabetermin noch zu erledigen
    + Umfang der geforderten Abgabe sollte zu Beginn bekannt sein, um besseren Zeitplan zu erstellen

## 11.5 Teilnehmer an dieser Aufgabe und ihre Rollen

+ Teammeeting am 09.07.2020:
  + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Fortführung der Programmierung zu Sonderterminen:
  + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Bearbeitung der Aufgaben für die Abgabe:
  + Kevin, Martin, Valeri, Saskia, Rashid, Tom
+ Integration Doxygen und Netlify Dokumentation:
  + Tim
+ Berichterstellung:
  + Tom, Saskia

## 11.6 Anlagen zum Bericht vom 08.07.2020

+ Code (siehe Master-Branch und Neben-Branches, SonarCloud und TravisCI)
+ Dokumentation: [Netlify](https://bibparser.timkante.dev "Doxygen")
+ Diagramme:
  + [Zustandsdiagramm 1][state1]
  + [Zustandsdiagramm 2][state2]
  + [Sequenzdiagramm 1][seq1]
  + [Sequenzdiagramm 2][seq2]

[state1]: ./../mileStone4/statediagram/Zustandsdia2.jpg "erstes neues Zustandsdiagramm"
[state2]: ./../mileStone4/statediagram/Zustandsdia3.jpg "zweites neues Zustandsdiagramm"
[seq1]: ./../mileStone4/sequenzdiagram/SequenzDia2.jpg "erstes neues Sequenzdiagramm"
[seq2]: ./../mileStone4/sequenzdiagram/SequenzDia3.jpg "zweites neues Sequenzdiagramm"
