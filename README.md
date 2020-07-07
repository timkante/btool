<img align="right" src="https://upload.wikimedia.org/wikipedia/de/thumb/e/e3/Logo_TU_Chemnitz.svg/2000px-Logo_TU_Chemnitz.svg.png" width="200" height="99.5"/>

<h1>Software-Engineering-Assignment <br/> summer semester 2020 <br/> BiB-Parser-Tool</h1>
<h2>TU-Chemnitz <br/> Faculty of Computer Science <br/> Professorship of Software Engineering</h2>

## Project Status

### Builds :construction_worker: and Deployments :rocket:

[![Netlify Status](https://api.netlify.com/api/v1/badges/c88170d7-f1a1-48d4-8e86-d8d1fdfb8afd/deploy-status)](https://app.netlify.com/sites/relaxed-heisenberg-aecc6d/deploys)
![Travis Badge](https://travis-ci.com/timkante/bibParser.svg?branch=master "TravisCI - Status")

### Code-Quality :art:

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=alert_status)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Technical Debt](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=sqale_index)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=bugs)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=timkante_bibParser)

## Project-Description :pencil:

A Tool to process `.bib`-Files like:

```raw
@inproceedings{someID,
    author = {Author A and Author B},
    title = {{Very, very fancy title}},
    booktitle = {A very serious collection of fancy stuff},
    year = {2013},
    pages = {1--18},
    month = Feb,
    publisher = {E-Corp},
}
@article{someID+42,
    author = {Author C},
    title = {{Is this a even more fancy title?}},
    booktitle = {Greatest collection of knowlage ever},
    year = {2019},
    pages = {154--164},
    month = May,
    publisher = {Anonymous},
    url = {https://www.anons.com/publications/docs/reallyfancy.pdf},
    file = {reallyfancy.pdf}
}
...
```
Takes the name of a style (article )
Nimmt den Namen eines Stils und eine Liste von Namen von [bib-Dateien](https://de.wikipedia.org/wiki/BibTeX) und produziert eine HTML-Ausgabedatei. Die Konvertierung wird mit Hilfe einer Übersetzungstabelle (semantische tags) durchgeführt, so dass es sehr einfach sein sollte, weitere Symbole hinzuzufügen und zu aktualisieren. Es sollte möglich sein, den Inhalt der erzeugten HTML-Datei nach Datum (d.h.: Jahr), Typ (d.h.: Zeitschrift, Konferenz usw.) oder Autoren-Namen zu sortieren und anzuordnen. Darüber hinaus sollte das Parser-Tool in der Lage sein, die bib-Dateien zu bearbeiten und zu aktualisieren. Das bib-Parser-Werkzeug wäre in der Lage, den Inhalt einer bib-Datei in andere Formate als HTML zu konvertieren, wie z.B. XML- oder PDF-Dateien (gut zu haben).

## Team

Gruppenmitglieder für Group1:

+ Herr Valeri Fitz (Projektmanager)
+ Herr Kevin Diex
+ Frau Saskia Heinrich
+ Herr Tim Kante
+ Herr Rashid Katamesh
+ Herr Tom Seidel
+ Herr Martin Zeidler

## Meilensteine

[Meilenstein 1 - KW 18](doc/milestone1/berichtGroup1KW18.md "Bericht der KW 18")

[Meilenstein 2 - KW 19](doc/milestone2/berichtGroup1KW19.md "Bericht der KW 19")

[Meilenstein 3 - KW 20](doc/milestone3/berichtGroup1KW20.md "Bericht der KW 20")

[Meilenstein 4 - KW 21](doc/milestone4/berichtGroup1KW21.md "Bericht der KW 21")

---

[Bericht - KW 22](doc/Berichte/berichtGroup1KW22.md "Bericht der KW 22")

[Bericht - KW 23](doc/Berichte/berichtGroup1KW23.md "Bericht der KW 23")

[Bericht - KW 24](doc/Berichte/berichtGroup1KW24.md "Bericht der KW 24")

[Zwischenbericht - KW 25](doc/Berichte/Zwischenbericht.md "Zwischenbericht der KW 25")

[Bericht - KW 26](doc/Berichte/berichtGroup1KW26.md "Bericht der KW 26")

[Bericht - KW 27](doc/Berichte/berichtGroup1KW27.md "Bericht der KW 27")

[Bericht - KW 28](doc/Berichte/berichtGroup1KW28.md "Bericht der KW 28")

## Links

Für alle Informationen zum aktuellen CI-Status: [TravisCI](https://travis-ci.com/github/timkante/bibParser "TravisCI")

Für ausführliche Code-Analyse: [SonarCloud](https://sonarcloud.io/dashboard?id=timkante_bibParser "SonarCloud.io")

Dokumentation: [Netlify](https://bibparser.timkante.dev "Doxygen")
