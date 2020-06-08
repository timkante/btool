//
// Created by Martin on 03.06.2020.
//

#include "Parser.hpp"
#include "FileGenerator.hpp"
#include "StyleProperties.hpp"
#include "BibElement.hpp"
#include "StyleProperties.hpp"

Parser::Parser(std::string ruleFile, std::vector<std::string> bibFiles, std::string targetStyle) {
    TranslationTable = new TranslationTable(ruleFile);
    if (bibFiles.size() == 1){
        parseFile(bibFiles[0], targetStyle);
    }
    else{
        parseFiles(bibFiles, targetStyle);
    }
}
void Parser::generate(const std::string sorting, const std::string format){
    Outputfile = new FileGenerator(parsedElements, format, sorting);
}
void Parser::parseFile(std::string fileName, std::string targetStyle){
    parseElement();
}
void Parser::parseFiles(std::vector<std::string> &fileName, std::string targetStyle){
    parseElement();
}
void Parser::parseField(std::string field, StyleProperties::checkAgainst){

    BibElement = new BibElement(id , styles.name, /*vector*/);
}
void Parser::parseElement(std::string element, StyleProperties::styles){
    styles = TranslationTable.getStyle();
    parseField("author", styles);
}