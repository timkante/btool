# 10 Bericht vom 08.07.2020
  
## 10.1  Was ist seit der letzten Woche passiert

+ Besprechung zur Endpräsentation (Bestandteile der Abgabe.pdf)
  + Aufteilung der neuen Aufgaben zwischen Teilgruppen:
    + Volere Snow Cards (funktionale Anforderungen) --> Valeri, Saskia, Rashid
    + Volere Snow Cards (nicht-funktionale Anforderungen) --> Kevin, Martin, Tom
    + Use-Case-Diagramme --> Kevin, Martin, Tom
    + Zustands- und Sequenzdiagramme --> Valeri, Saskia, Rashid
    + Doxygen- und Netlify-Integration für Code-Dokumentation --> Tim
    + CRC-Karten aktualisieren, ab KW 29
  + Terminvorschlag für Endpräsentation :
    + Live-Vorstellung des Projektes
    + Donnerstag, 20.08.2020
+ Weiterführung der Implementierungen der Klassen
  + Tim: TranslationTable
    + Status: ...
  + Saskia, Valeri, Rashid:  FileGenerator, XML
    + Status: FileGenerator wurde weiter implementiert. Einigung, dass Ausgabeformat nur auf XML zu beschränken. Keine PDF-Implementierung, weil keine passenden Bibliotheken auffindbar.
  + Kevin, Tom, Martin: Parser
    + Status: ...
+ Implementierung von Kommentaren im Code mittels Doxygen

## 10.2 Was waren die Herausforderungen und Probleme? Wie wurden sie gelöst

+ vollständig korrekte Implementierung der Klassen benötigt Zeit
  + zusätzlich zum Code müssen Tests geschrieben werden, welche ebenfalls relativ viel Zeit benötigen
+ Ausfall des montägigen Meetings, weil mehr Zeit für Bearbeitung der neuen Aufgaben und Programmierung benötigt wurde.
  + dadurch fehlende Kommunikation zwischen den Programmiergruppen
+ Bearbeitung der neuen Aufgaben kostet zusätzlich viel Zeit. Bearbeitung während Prüfungsphase nicht möglich
  + Aufteilung der neuen Aufgaben zwischen Teilgruppen

## 10.3 Was lief gut? Was lief nicht gut

### 10.3.1 Was lief gut

+ Aufteilung der neuen Aufgaben zwischen Teilgruppen
+ Gruppenübergreifende Hilfestellung bei der Implementierung der Klassen

### 10.3.2 Was lief nicht gut

+ Unerwartet hoher zeitlicher Aufwand, weil bereits erstellte Aufgaben (siehe Meilenstein 1 bis 4) wiederholt und ergänzt werden müssen
+ Weniger Bearbeitungszeit für Aufgaben aufgrund bevorstehender Klausuren vorhanden

## 10.4 Was haben Sie gelernt? Was würden Sie beim nächsten Mal anders machen

### 10.4.1 Was haben Sie gelernt

+ Besseres Verständnis durch Ergänzung und Wiederholung der ersten Meilensteine (SnowCards usw.)
+ besseres Verständnis für Dokumentation des Quellcodes durch Doxygen

### 10.4.2 Was würden Sie beim nächsten Mal anders machen

+ Empfehlung an folgende Semester: Aufwand der Aufgaben für die Endpräsentation (Anzahl der von SnowCards usw.) früher erfragen

## 10.5 Teilnehmer an dieser Aufgabe und ihre Rollen

+ Teammeeting am 02.07.2020:
  + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Fortführung der Programmierung zu Sonderterminen:
  + Kevin, Martin, Valeri, Saskia, Rashid, Tim, Tom
+ Volere Snow Cards (funktionale Anforderungen):
  + Valeri, Saskia, Rashid
+ Volere Snow Cards (nicht-funktionale Anforderungen):
  + Kevin, Martin, Tom
+ Integration Doxygen und Netlify Dokumentation:
  + Tim
+ Berichterstellung:
  + Rashid, Valeri

## 10.6 Anlagen zum Bericht vom 08.07.2020

+ Code (siehe Master-Branch und Neben-Branches, SonarCloud und TravisCI)
+ Dokumentation: [Netlify](https://bibparser.timkante.dev "Doxygen")
+ SnowCards
  + [Funktionale Anforderung ID 001-005][func]
  
  + [Nicht-Funktionale Anforderungen ID 006][nonFunc6]
  + [Nicht-Funktionale Anforderungen ID 007][nonFunc7]
  + [Nicht-Funktionale Anforderungen ID 008][nonFunc8]

[func]: ./../snowCards/functional/snowCardFunctional.md "SnowCard für funktionale Anforderungen"
[nonFunc8]: ./../snowCards/nonFunctional/snowCardNonFuctional.md "SnowCard für nicht funktionale Anforderungen"
[nonFunc6]: ./../snowCards/nonFunctional/snowCardNonFuctional006.md "SnowCard für nicht funktionale Anforderungen"
[nonFunc7]: ./../snowCards/nonFunctional/snowCardNonFuctional007.md "SnowCard für nicht funktionale Anforderungen"
