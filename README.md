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
Takes the name of a style (article, inproceedings, book, etc.), a collection of [`.bib`-Files](https://de.wikipedia.org/wiki/BibTeX) and a Property (title, author, year, etc.) to sort after, and produces a nicely formatted HTML-File with an overview over all the Publications in the given files matching the given style, ordered by the given ordering.  
The Tool uses a JSON-File with rules containing names of known styles and their required and optional fields. :wrench:  
The rule-table is easily editable and adding styles or fields will be a breeze. :sparkles:

## Installation :rocket:

### Prerequisites :seedling:

#### Boost-Library

__Boost with a minimum version of `1.50`__  
Follow the official boost instructions for [linux/mac](https://www.boost.org/doc/libs/1_73_0/more/getting_started/unix-variants.html) or [windows](https://www.boost.org/doc/libs/1_73_0/more/getting_started/windows.html) to install and compile it on your machine.  

### CMake

__CMake with a minimum version of `3.15`__
Follow the [official cmake instructions](https://cmake.org/download/) to get yourself a running version of cmake.

### Build :construction_worker:

1. __Clone the Repo and Submodules:__

    ```bash
    $ git clone --recursive git@github.com:timkante/bibParser.git
    ```

2. __cd into the project:__

    ```bash
    $ cd bibParser
    ```

3. __Create a build directory and cd into it:__

    ```bash
    $ mkdir build && cd build
    ```

4. __Run the CMake target:__

    ```bash
    $ cmake ..
    ```

5. __Build a target:__

    5.1. __For building the Tests:__
    
    ```bash
    $ make bibParserTests
    ```
   
    5.2. __For building the Executable:__
   
    ```bash
    $ make bibParserRun
    ```

6. __Run a target:__

    6.1. __For running the Tests:__
    
    ```bash
    $ ./test/bibParserTests
    ```
   
    6.2. __For running the Executable:__
   
    ```bash
    $ ./bibParserRun <YOUR_ARGUMENTS>
    ```

## Team :busts_in_silhouette:

Group-Members of Group 1:

+ Valeri Fitz (Project-Manager)
+ Kevin Diex
+ Saskia Heinrich
+ Tim Kante
+ Rashid Katamesh
+ Tom Seidel
+ Martin Zeidler

## Milestones :triangular_flag_on_post:

[Milestone 1 - KW 18](doc/milestone1/berichtGroup1KW18.md "Report of KW 18")

[Milestone 2 - KW 19](doc/milestone2/berichtGroup1KW19.md "Report of KW 19")

[Milestone 3 - KW 20](doc/milestone3/berichtGroup1KW20.md "Report of KW 20")

[Milestone 4 - KW 21](doc/milestone4/berichtGroup1KW21.md "Report of KW 21")

## Reports

[Report - KW 22](doc/Berichte/berichtGroup1KW22.md "Report of KW 22")

[Report - KW 23](doc/Berichte/berichtGroup1KW23.md "Report of KW 23")

[Report - KW 24](doc/Berichte/berichtGroup1KW24.md "Report of KW 24")

[Report - KW 25](doc/Berichte/Zwischenbericht.md "Report of KW 25")

[Report - KW 26](doc/Berichte/berichtGroup1KW26.md "Report of KW 26")

[Report - KW 27](doc/Berichte/berichtGroup1KW27.md "Report of KW 27")

[Report - KW 28](doc/Berichte/berichtGroup1KW28.md "Report of KW 28")

## Links

Für alle Informationen zum aktuellen CI-Status: [TravisCI](https://travis-ci.com/github/timkante/bibParser "TravisCI")

Für ausführliche Code-Analyse: [SonarCloud](https://sonarcloud.io/dashboard?id=timkante_bibParser "SonarCloud.io")

Dokumentation: [Netlify](https://bibparser.timkante.dev "Doxygen")
