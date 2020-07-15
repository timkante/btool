# 9 Bericht vom 01.07.2020
  
## 9.1  Was ist seit der letzten Woche passiert

+ Weiterführung der Implementierungen der Klassen
    + Tim: TranslationTable 
        + Status: Speichrung des gesuchten Styles in die StyleProperties über die Vorgabe der .json funktioniert 
    + Tom, Valeri: Field und BibElement fertiggestellt
    + Saskia, Rashid: StyleProperties fertiggestellt
    + Saskia, Valeri, Rashid:  FileGenerator
        + Status: Funktionsköpfe der einzelnen Ausgabeformate sind angelegt
    + Kevin, Tom, Martin: Parser
       + Status: Einlesen der Bib-Datei funktioniert; Bearbeitung des parsens in die BibElemente
+ Implementierung von Kommentaren im Code mittels Doxygen
+ Abänderung und Vervollständigung der .json-Datei

## 9.2 Was waren die Herausforderungen und Probleme? Wie wurden sie gelöst
+ vollständig korrekte Implementierung der Klassen benötigt Zeit
    + zusätzlich zum Code müssen Tests geschrieben werden, welche ebenfalls relativ viel Zeit benötigen
+ Ausfall des montägigen Meetings (viele hatten keine Zeit)
    + dadurch fehlende Kommunikation zwischen den Programmiergruppen

## 9.3 Was lief gut? Was lief nicht gut

### 9.3.1 Was lief gut
+ gute und verständliche Einführung in Doxygen
+ Gruppenübergreifende Hilfestellung bei der Implementierung der Klassen

### 9.3.2 Was lief nicht gut
+ Überschneidung des montägigen Meetings mit anderen Veranstalltungen, weshalb es nicht zustande kam
+ da die meisten Nutzer wenige Kentnisse über die Bibliotek Boost haben, kam es zu kleinen Komplikationen
    + z.B.: erkannte Boost die Einbindung von Regex nicht, was bei der Lösung dieses Problemes einige Zeit beanspruchte

## 9.4 Was haben Sie gelernt? Was würden Sie beim nächsten Mal anders machen

### 9.4.1 Was haben Sie gelernt
+ besserer Umgang mit Boost
+ besseres Verständniss für Regex 
    + z.B.: die Gruppenoption

### 9.4.2 Was würden Sie beim nächsten Mal anders machen

+ bessere Kommunikation zwischen den Programmiergruppen 

## 9.5 Teilnehmer an dieser Aufgabe und ihre Rollen

+ Teammeeting am 25.06.2020:
    + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Fortführung der Programmierung zu Sonderterminen:
    + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Berichterstellung:
    Kevin, Martin
## 9.6 Anlagen zum Bericht vom 01.07.2020
+ Code (siehe Master-Branch und Neben-Branches, SonarCloud und TravisCI)
