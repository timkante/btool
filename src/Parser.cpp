#include "Parser.hpp"
//#include "FileGenerator.hpp"
#include "StyleProperties.hpp"
#include "BibElement.hpp"
#include "StyleProperties.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

void checkFolder(std::string path);


Parser::Parser(std::string ruleFile, const std::string targetStyle, TranslationTable translationTable)
    :ruleFile(std::move(ruleFile)), targetStyle(std::move(targetStyle)), translationTable(translationTable) {};

void Parser::generate(const std::string sorting, const std::string format){
    //FileGenerator outputfile = new FileGenerator(parsedElements, format, sorting);
}

std::vector<BibElement> Parser::parseFile(boost::filesystem::ifstream &fsStream){
    BibElement bibElem = parseElement("",StyleProperties());
    std::vector<BibElement> bibElems = {bibElem};

    std::string str;
    while(std::getline(fsStream, str)){
        std::cout << str << std::endl;
    }

    return bibElems;
}
void Parser::parseFiles(std::string path){
    checkFolder(path);

    boost::filesystem::path p = {path};
    boost::filesystem::directory_iterator it{p};
    bool bibFound = false;
    while (it != boost::filesystem::directory_iterator{}) {
        std::string fileExt = boost::filesystem::extension(*it);
        if(fileExt.compare(".bib") == 0){
            std::cout << "Folgende Datei wird eingelesen: " << *it << std::endl;
            bibFound = true;
            boost::filesystem::ifstream in(*it);
            parseFile(in);
        }
        *it++;
    }
    if(!bibFound){
        std::cout << "Keine Bib Files im Pfad gefunden!\nOrdnerpfad mit Bib's eingeben:\n";
        std::cin >> path;
        parseFiles(path);
    }
}

Field Parser::parseField(std::string field, StyleProperties checkAgainst){
    //BibElement bibElement = new BibElement(id , styles.name, /*vector*/);
    Field f = Field("name", "value", false);
    return f;
}

BibElement Parser::parseElement(std::string element, StyleProperties style){
    //style = translationTableranslationTable.getStyle(targetStyle);
    //parseField(targetStyle ,style);
    std::vector<Field> fields = {Field("name", "value", false)};
    BibElement bibElem = BibElement("id", "style", fields);
    return bibElem;
}

void checkFolder(std::string path) {
    while (!boost::filesystem::is_directory(path)){
        std::cout << "Kein Ordner!\n";
        std::cout << "Ordner angeben\n";
        std::cin >> path;
    }
}