//
// Created by Martin on 03.06.2020.
//

#ifndef BIBPARSER_PARSER_HPP
#define BIBPARSER_PARSER_HPP
#include <BibElement.cpp>
#include <TranslationTable.cpp>
#include <vector>
#include <string>
#include <BibElement.hpp>
#include <Field.hpp>

class Parser {
private:
    std::vector<BibElement> parsedElements; //statt int -> BibElemente
public:
    TranslationTable::TranslationTable;
    Parser(std::string ruleFile, std::vector<std::string> bibFiles, std::string targetStyle;);  //vektor mit Dateipfad stings
    void generate(const std::string sorting, const std::string format);
    void parseFile(std::string fileName, std::string targetStyle);
    void parseFiles(std::vector<std::string> &fileName, std::string targetStyle);
    void parseField(std::string field, StyleProerties::checkAgainst);
    void parseElement(std::string element, StyleProerties::styles);
};


#endif //BIBPARSER_PARSER_HPP
