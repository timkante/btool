# SnowCard Nicht-Funktionale Anforderung

## ID

ID: 009

## Req-Type

Nicht-funktional / Zuverlässigkeit

## Events / Use-Cases

Parsen

## Description

Kommt es zu einem Fehler während des Parsens, soll der Vorgang des Parsens abgebrochen werden. Der Anwender soll eine eindeutige Fehlermeldung mit dem Verweis auf die ID des betreffenden Elementes in der .bib - Datei erhalten / angezeigt bekommen.

## Rationale

Das Abbrechen des Parsens soll die Zuverlässigkeit des Programms garantieren. Dadurch können Fehlerhafte Ausgaben bzw. Ausgabeformate vermieden werden.

## Originator

Anwender

## Fit Criterion

bekannte und mögliche Fehlerfälle werden durch Tests (GTest) provoziert und ausgewertet

## Customer Satisfaction

[3/5]

## Customer Dissatisfaction

[3/5]

## Priority

[3/5]

## Supporting Material

Keine

## Conflicts

Keine

## History

Kevin Diex,
Martin Zeidler,
Tom Seidel

07\. 07\. 2020

Version 1.0.0
