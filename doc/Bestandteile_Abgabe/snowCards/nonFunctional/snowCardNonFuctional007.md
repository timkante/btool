# SnowCard Nicht-Funktionale Anforderung

## ID

ID: 007

## Req-Type

Nicht-funktional / Perfomance

## Events / Use-Cases

Dauer des Parsing-Vorgangs

## Description

Der Vorgang des Parsens einer .bib - Datei mit 100 Einträgen eines Stils soll unter 500 ms bis zur Vorbereitung der Ausgabe in das entsprechende Format dauern. 

## Rationale

Damit wird ein nahezu Verzögerungsfreier Ablauf für den Anwender gewährleistet.

## Originator

Anwender

## Fit Criterion

Es wird ein Test (mittels GTest Suite) geschrieben, welcher die exate Ausführungszeit des Parsens überwacht.

## Customer Satisfaction

[5/5]

## Customer Dissatisfaction

[2/5]

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
