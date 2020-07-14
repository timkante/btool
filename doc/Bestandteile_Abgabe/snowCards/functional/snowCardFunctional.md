# SnowCard Funktionale Anforderung

## ID

ID: 001

## Req-Type

Arbeitsumfang

## Events / Use-Cases

 Jeder commit (Änderung / neu hinzugefügter Quellcode) auf GitHub wird automatisch ausgewertet und die Zeitpunkte und Inhalte der Änderungen optisch aufbereitet dargestellt.

## Description

Der Zeitpunkt, der Inhalt und der Autor jeder Änderung im kompletten Programmcode sind auf der Plattform Github öffentlich einsehbar. 

## Rationale

Es kann nachvollzogen werden wer zu welchem Zeitpunkt eine Änderung vollzogen hat, wodurch automatisch eine Dokumentation der Projekterstellung generiert wird.

## Originator

Programmierer

## Fit Criterion

Änderungsübersicht (Historie) in GitHub öffnen. 

## Customer Satisfaction

[0/5]

Für Kunden irrelevant.

## Customer Dissatisfaction

[0/5]

Für Kunden irrelevannt.

## Priority

[5/5]

Hohe Priorität im Projekt, da diese Anforderung den Erfolg des Projektes ausmacht.

## Supporting Material

Historie in GitHub 

## Conflicts

Keine.

## History

Valeri Fitz, 
Rashid Katamesh,
Saskia Heinrich

06\. 07\. 2020

Version 0.1.0


## ID

ID: 002

## Req-Type

Arbeitsumfang

## Events / Use-Cases

 Bei jeder Arbeit am Projekt (Programmierung, Klassendiagramme, Planung, Diskussionen, ...)

## Description

Jede Woche wird ein Bericht / Meilenstein zum Projektfortschritt verfasst.

## Rationale

Der Projektfortschritt, Arbeitsaufteilung, Zeitaufwand und mögliche Konflikte und daraus resultierende Änderungen müssen nachvollzogen werden können.

## Originator

Projektmanagement

## Fit Criterion

Berichtüberischt (ReadMe) in GitHub öffnen.  Jede Woche muss ein Bericht veröffentlich werden.

## Customer Satisfaction

[5/5]

Kunde kann Projektfortschritt / Einhaltung des Zeitplans nachvollziehen. 

## Customer Dissatisfaction

[2/5]

Kunde kann ohne leben.

## Priority

[5/5]

Hohe Priorität im Projekt, da diese Anforderung den Erfolg des Projektes ausmacht.

## Supporting Material

Berichtübersicht (ReadMe) in GitHub 

## Conflicts

Keine.

## History

Valeri Fitz, 
Rashid Katamesh,
Saskia Heinrich

06\. 07\. 2020

Version 0.1.0



## ID

ID: 003

## Req-Type

Abgrenzung des Produktes

## Events / Use-Cases

 Bei jeder Arbeit am Projekt (Programmierung, Klassendiagramme, Planung, Diskussionen, ...)

## Description

Das Produkt gibt die eingelesene bib-Datei nach interner Verarbeitung als XML-Datei aus.

## Rationale

Die interne Verarbeitung der bib-Datei muss gespeichert werden können. Die Ausgabe im XML-Format ist einfach zu programmieren.

## Originator

Programmierer

## Fit Criterion

Test-Driven-Development, Nach Durchlaufen des Programms wurde eine XML-Datei erstellt, die den Inhalt der bib-Datei enthält.

## Customer Satisfaction

[5/5]

Kunde kann Programm anwenden.

## Customer Dissatisfaction

[0/5]

Kunde kann Verarbeitung im Programm nicht erkennen.

## Priority

[5/5]

Hohe Priorität im Projekt, da diese Anforderung die erfolgreiche Arbeit des Produktes ausgibt.

## Supporting Material

GoogleTest, Quellcode

## Conflicts

Keine.

## History

Valeri Fitz, 
Rashid Katamesh,
Saskia Heinrich

06\. 07\. 2020

Version 0.1.0



## ID

ID: 004

## Req-Type

Anforderungen an Funktionen und Daten des Produktes

## Events / Use-Cases

Aufruf des Programms aus der Kommandozeile

## Description

Die zu parsende Datei muss eine bib-Datei sein.

## Rationale

Der Parser orientiert sich an den Regeln zum Aufbau einer bib-Datei und erwartet dieses Format.

## Originator

Kunde

## Fit Criterion

Die zu verarbeitende Datei besitzt eine '.bib' Endung und hält die Regeln zum Aufbau einer bib-Datei ein.

## Customer Satisfaction

[5/5]

Spezifikation des Kunden wurde eingehalten.

## Customer Dissatisfaction

[0/5]

Spezifikation des Kunden wurde nicht eingehalten.

## Priority

[5/5]

Hohe Priorität im Projekt, da diese Anforderung die erfolgreiche Arbeit des Produktes ausmacht.

## Supporting Material

[BibTex Format Beschreibung ](http://www.bibtex.org/Format/de/) 

## Conflicts

Keine.

## History

Valeri Fitz, 
Rashid Katamesh,
Saskia Heinrich

06\. 07\. 2020

Version 0.1.0



## ID

ID: 005

## Req-Type

Anforderungen an Funktionen und Daten des Produktes

## Events / Use-Cases

Start des Programms

## Description

Das Produkt kann aus der Kommandozeile heraus gestartet werden.

## Rationale

Einfache Umsetzung des Programmaufrufes ohne GUI. Keine Einarbeitung notwendig, da nur Parameter im Aufruf spezifiziert werden, welche in einer help-Datei erklärt werden.

## Originator

Programmierer

## Fit Criterion

Start der Kommandozeile und Aufruf des Programms

## Customer Satisfaction

[5/5]

Kunde kann Programm einfach starten

## Customer Dissatisfaction

[0/5]

Kunde benötigt mehr Einarbeitungszeit

## Priority

[5/5]

Hohe Priorität im Projekt, da diese Anforderung die erfolgreiche Arbeit des Produktes ausmacht.

## Supporting Material

BibParserTool.exe

## Conflicts

Keine.

## History

Valeri Fitz, 
Rashid Katamesh,
Saskia Heinrich

06\. 07\. 2020

Version 0.1.0