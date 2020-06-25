#include "Parser.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
//#include "FileGenerator.hpp"

void checkFolder(const boost::filesystem::path& path);


Parser::Parser(std::string ruleFile, const std::string targetStyle, TranslationTable translationTable)
    :ruleFile(std::move(ruleFile)), targetStyle(std::move(targetStyle)), translationTable(translationTable) {};

void Parser::generate(const std::string sorting, const std::string format){
    //FileGenerator outputfile = new FileGenerator(parsedElements, format, sorting);
}

std::vector<BibElement> Parser::parseFile(boost::filesystem::ifstream &fsStream){
    BibElement bibElem = parseElement("",StyleProperties());
    std::vector<BibElement> bibElems = {bibElem};
    std::vector<std::string> style;
    std::vector<std::vector<std::string>> allStyles;
    std::string line;
    boost::regex expr{"\\@(.*)\\{(.*)\\,"};
    boost::smatch group;
    while(std::getline(fsStream, line)){
        boost::trim(line);
        // (line.find('@') != std::string::npos) {
        if(boost::regex_search(line, group, expr)){
            if (!(allStyles.empty() && style.empty())) {
                allStyles.insert(allStyles.end(), style);
                style.clear();
                std::cout << "ID " << group[2] << std::endl << "Style " << group[1];
            }
        }
        if(!line.empty()) {
            style.insert(style.end(), line);
        }
    }
    allStyles.insert(allStyles.end(), style);

    return bibElems;
}
void Parser::parseFiles(const boost::filesystem::path& path){
    checkFolder(path);

    boost::filesystem::directory_iterator it{path};
    bool bibFound = false;
    while (it != boost::filesystem::directory_iterator{}) {
        std::string fileExt = boost::filesystem::extension(*it);
        if(fileExt.compare(".bib") == 0){
            bibFound = true;
            boost::filesystem::ifstream in(*it);
            parseFile(in);
        }
        *it++;
    }
    if(!bibFound){
        std::cout << "Keine Bib Files im Pfad gefunden!\n";
        std::cout << path.string() << std::endl;
    }
}

Field Parser::parseField(std::string field, StyleProperties checkAgainst){
    //BibElement bibElement = new BibElement(id , styles.name, /*vector*/);
    Field f = Field("name", "value");
    return f;
}

BibElement Parser::parseElement(std::string element, StyleProperties style){
    //style = translationTableranslationTable.getStyle(targetStyle);
    //parseField(targetStyle ,style);
    std::vector<Field> fields = {Field("name", "value")};
    BibElement bibElem = BibElement("id", "style", fields);
    return bibElem;
}

void checkFolder(const boost::filesystem::path& path) {
    if (!boost::filesystem::is_directory(path)){
        std::cout << "Kein Ordner!\n";
    }
}