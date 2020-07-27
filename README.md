<img align="right" src="https://upload.wikimedia.org/wikipedia/de/thumb/e/e3/Logo_TU_Chemnitz.svg/2000px-Logo_TU_Chemnitz.svg.png" width="200" height="99.5"/>

<h1>Software-Engineering-Assignment <br/> summer semester 2020 <br/> BiB-Parser-Tool</h1>
<h2>TU-Chemnitz <br/> Faculty of Computer Science <br/> Professorship of Software Engineering</h2>

## Project Status :octocat:

### Builds :construction_worker: and Deployments :rocket:

[![Netlify Status](https://api.netlify.com/api/v1/badges/c88170d7-f1a1-48d4-8e86-d8d1fdfb8afd/deploy-status)](https://app.netlify.com/sites/relaxed-heisenberg-aecc6d/deploys)
[![Build Status](https://travis-ci.com/timkante/btool.svg?branch=master)](https://travis-ci.com/timkante/btool)

### Code-Quality :art::nail_care:

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=alert_status)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Technical Debt](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=sqale_index)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=bugs)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=timkante_bibParser)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=timkante_bibParser&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=timkante_bibParser)

## Table of contents
+ [What is this Repo?](#project-description-pencil)
+ [How to use the Code](#installation-rocket)
  + [Prerequisites](#prerequisites-seedling)
    + [Boost](#boost-library)
    + [CMake](#cmake)
  + [Build the Source](#build-construction_worker)
+ [How to use the program](#usage-sparkles)
  + [Program options](#basic-program-options)
  + [Usage constraints](#usage-constraints)
  + [Examples](#examples)
  + [Translation-Tables](#using-a-translation-table)
+ [What is this project built with?](#built-with-heart-and)
+ [Contributors](#team-busts_in_silhouette)
+ [Milestones](#milestones-triangular_flag_on_post)
+ [Reports](#reports-pencil)
+ [Resources and Tools](#links-link)
+ [Required tasks](#required-tasks-pencil)
+ [Further reading](#links-link)

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

#### CMake

__CMake with a minimum version of `3.15`__
Follow the [official cmake instructions](https://cmake.org/download/) to get yourself a running version of cmake.

### Build :construction_worker:

1. __Clone the Repo and Submodules:__

    ```bash
    $ git clone --recursive git@github.com:timkante/btool.git
    ```

2. __cd into the project:__

    ```bash
    $ cd btool
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
    $ make btoolTest
    ```
   
    5.2. __For building the Executable:__
   
    ```bash
    $ make btool
    ```

6. __Run a target:__

    6.1. __For running the Tests:__
    
    ```bash
    $ ./test/btoolTest
    ```
   
    6.2. __For running the Executable:__
   
    ```bash
    $ ./btool <YOUR_ARGUMENTS>
    ```

## Usage :sparkles:

### Basic program options:

+ `-h [ --help ]` print usage message
+ `-o [ --output ] arg (="stdout")` pathname for output (default is stdout)
+ `-t [ --table ] arg` full pathname of translation-table (can be used for extensive filtering)
+ `-i [ --input ] arg` file(s) to handle
+ `-H [ --html ]` set output-type to html
+ `-X [ --xml ]` set output-type to xml
+ `-f [ --filter ] arg` filter output for a style-name(s)
+ `-s [ --sort ] arg` sort output for a field

### Usage constraints:

+ Only one output-type can be selected (`--html` or `--xml`), if no type is given, plain-text will be used
+ Generating output always requires one or more files/directories as input (`--input`)

### Examples:

+ Show help message
```
btool --help
```

+ Generating a HTML page from a given directory of `.bib`-files, sorted by author, filtered by translation-table, outputting it to `./index.html`
```
btool -t ./tables/mytable.json -i ./files --html -s author -o index.html
```

+ Print results from a given set of of `.bib`-files, sorted by author, filtered for articles and books, to stdout
```
btool -i file1.bib file2.bib ./someMoreFiles -s author -f article booky
```

### Using a translation-table:

If you want to do more complex filtering of elements, not only filtering for styles, maybe using a translation-table can help you.  
Providing the Parser such a table, will make it filter for them.  
It will only generate Elements that match the constraints given by the table.  
So you have the ability to filter for styles with necessary fields and optional fields, Elements that don't have all necessary fields, or fields that are not necessary or optional, will get stripped off.  
You can combine translation-table filtering with the `--filter`-option if you want to.

The translation-table has to be of the following (JSON) format:

```typescript
type Table = {
  styles: Constraint[];
}

type Constraint = {
    name: String;
    requiredFields: String[];
    optionalFields: String[];
}
```

Here's an example:

```JSON
{
"styles": [
    {
      "name": "article",
      "requiredFields": [
        "author",
        "title",
        "year",
        "journal"
      ],
      "optionalFields": [
        "volume",
        "number",
        "pages",
        "month",
        "note"
      ]
    },
    {
      "name": "book",
      "requiredFields": [
        "author",
        "title",
        "year",
        "publisher"
      ],
      "optionalFields": [
        "volume",
        "series",
        "address",
        "edition",
        "month",
        "note",
        "isbn"
      ]
    },
    {
      "name": "proceedings",
      "requiredFields": [
        "title",
        "year"
      ],
      "optionalFields": [
        "volume",
        "pages",
        "address",
        "edition",
        "editor",
        "month",
        "note",
        "organization",
        "publisher"
      ]
    }
  ]
}
```

## Built with :heart: and

| | technology | purpose |
|---|---|---|
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/612px-ISO_C%2B%2B_Logo.svg.png" width="60" /> | [C++](https://www.cplusplus.com/) | speed |
| <img src="https://travis-ci.org/images/logos/TravisCI-Mascot-1.png" width="60" />| [Travis-CI](https://travis-ci.com/github/timkante/btool) | CI/CD |
| <img src="https://pbs.twimg.com/profile_images/955394530806829056/LC7DAYM3_400x400.jpg" width="60" /> | [SonarQube/SonarCloud](https://sonarcloud.io/dashboard?id=timkante_bibParser) | code-quality |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/Cmake.svg/2072px-Cmake.svg.png" width="60" /> | [CMake](https://cmake.org/) | builds |
| <img src="https://cdn.worldvectorlogo.com/logos/netlify.svg" width="60" /> | [Netlify](https://btool.timkante.dev/) | documentation |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/Octicons-mark-github.svg/1200px-Octicons-mark-github.svg.png" width="60" /> | [GitHub](https://github.com/timkante/btool) | version-control |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/53/Google_%22G%22_Logo.svg/1200px-Google_%22G%22_Logo.svg.png" width="60" /> | [googletest](https://github.com/google/googletest) | testing |
| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/48/Markdown-mark.svg/1200px-Markdown-mark.svg.png" width="60" /> | [Markdown](https://markdown.de/) | non-code-documentation
| <img src="https://www.seo-denda.de/wp-content/uploads/2019/07/bootstrap-logo.png" width="60" /> | [Bootstrap](https://getbootstrap.com/) | HTML-Beautification
| | [Doxygen](https://www.doxygen.nl/index.html) | documentation |
| | [spdlog](https://github.com/gabime/spdlog) | logging |
| | [CTML](https://github.com/tinfoilboy/CTML) | HTML-Generation |

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

## Reports :pencil:

[Report - KW 22](doc/Berichte/berichtGroup1KW22.md "Report of KW 22")  
[Report - KW 23](doc/Berichte/berichtGroup1KW23.md "Report of KW 23")  
[Report - KW 24](doc/Berichte/berichtGroup1KW24.md "Report of KW 24")  
[Report - KW 25](doc/Berichte/Zwischenbericht.md "Report of KW 25")  
[Report - KW 26](doc/Berichte/berichtGroup1KW26.md "Report of KW 26")  
[Report - KW 27](doc/Berichte/berichtGroup1KW27.md "Report of KW 27")  
[Report - KW 28](doc/Berichte/berichtGroup1KW28.md "Report of KW 28")  
[Report - KW 29](doc/Berichte/berichtGroup1KW29.md "Report of KW 29")

## Required tasks :pencil:

+ Volere SnowCards
    + functional:
        + [SnowCard 001](doc/snowCards/functional/snowCardFunctional001.md)
        + [SnowCard 002](doc/snowCards/functional/snowCardFunctional002.md)
        + [SnowCard 003](doc/snowCards/functional/snowCardFunctional003.md)
        + [SnowCard 004](doc/snowCards/functional/snowCardFunctional004.md)
        + [SnowCard 005](doc/snowCards/functional/snowCardFunctional005.md)
    + nonfunctional:
        + [SnowCard 006](doc/snowCards/nonFunctional/snowCardNonFuctional006.md)
        + [SnowCard 007](doc/snowCards/nonFunctional/snowCardNonFuctional007.md)
        + [SnowCard 008](doc/snowCards/nonFunctional/snowCardNonFuctional008.md)
        + [SnowCard 009](doc/snowCards/nonFunctional/snowCardNonFuctional009.md)
        + [SnowCard 010](doc/snowCards/nonFunctional/snowCardNonFuctional010.md)
        + [SnowCard 011](doc/snowCards/nonFunctional/snowCardNonFuctional011.md)
+ [CRC-Cards](doc/CRC_Cards/crcCards.md)
+ [class diagram](doc/milestone3/Klassendiagramm.vpd.png)
+ use-case diagrams
    + [Start of bib-Parse](doc/milestone4/usecases/uc-start.png)
    + [Print help of bib-Parser](doc/milestone4/usecases/uc-hilfe.png)
    + [Sort entries](doc/milestone4/usecases/uc-sort.png)
+ sequence diagrams
    + [sequence diagram 001](doc/milestone4/sequenzdiagram/SequenzDia.jpg)
    + [sequence diagram 002](doc/milestone4/sequenzdiagram/SequenzDia2.jpg)
    + [sequence diagram 003](doc/milestone4/sequenzdiagram/SequenzDia3.jpg)
+ state diagrams
    + [state diagram 001](doc/milestone4/statediagram/Zustandsdia.png)
    + [state diagram 002](doc/milestone4/statediagram/Zustandsdia2.jpg)
    + [state diagram 003](doc/milestone4/statediagram/Zustandsdia3.jpg)

## Links :link:

For the current CI-Status/Report [TravisCI](https://travis-ci.com/timkante/btool "TravisCI")  
For Code-Analysis: [SonarCloud](https://sonarcloud.io/dashboard?id=timkante_bibParser "SonarCloud")  
Documentation: [Netlify](https://btool.timkante.dev "Doxygen")
