#include "Parser.hpp"
//#include "FileGenerator.hpp"
#include "StyleProperties.hpp"
#include "BibElement.hpp"
#include "StyleProperties.hpp"

Parser::Parser(std::string ruleFile, std::vector<std::string> bibFiles, const std::string targetStyle)
    :ruleFile(std::move(ruleFile)), bibFiles(std::move(bibFiles)), targetStyle(std::move(targetStyle)) {};

void Parser::generate(const std::string sorting, const std::string format){
    //FileGenerator outputfile = new FileGenerator(parsedElements, format, sorting);
}

std::vector<BibElement> Parser::parseFile(std::string fileName){

}
void Parser::parseFiles(std::vector<std::string> fileName){
    for (std::vector<std::string>::iterator file = fileName.begin() ; file != fileName.end(); ++file){
        parseFile(*file);
    }
}

Field Parser::parseField(std::string field, StyleProperties checkAgainst){
    //BibElement bibElement = new BibElement(id , styles.name, /*vector*/);
}

BibElement Parser::parseElement(std::string element, StyleProperties style){
    //style = translationTableranslationTable.getStyle(targetStyle);
    //parseField(targetStyle ,style);
}