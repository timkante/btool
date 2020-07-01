#include "Parser.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <regex>
//#include "FileGenerator.hpp"

void checkFolder(const boost::filesystem::path& path);


Parser::Parser(std::string ruleFile, const std::string targetStyle, TranslationTable translationTable)
    :ruleFile(std::move(ruleFile)), targetStyle(std::move(targetStyle)), translationTable(translationTable) {};

void Parser::generate(const std::string sorting, const std::string format){
    //FileGenerator outputfile = new FileGenerator(parsedElements, format, sorting);
}

std::vector<BibElement> Parser::parseFile(boost::filesystem::ifstream &fsStream){
    BibElement bibElem = parseElement("",StyleProperties());
    std::vector<BibElement> bibElems = {};
    std::vector<std::string> style;
    std::vector<std::vector<std::string>> allStyles;
    std::string line;
    std::regex expr{"\\@(.*)\\{(.*)\\,"};
    std::regex fieldExpr{"(.*)=(.*)"};
    std::smatch group;
    bool styleMatch = false;
    std::string fieldName;
    std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    Field field = Field("","");
    std::vector<Field> bibFields;
    while(std::getline(fsStream, line)){
        boost::trim(line);
        // (line.find('@') != std::string::npos) {
        if(std::regex_search(line, group, expr)){
            //if (!(allStyles.empty() && style.empty())) {
                styleMatch = group[1]==targetStyle;
                if (styleMatch) {
                    if (!(field.name == "")){
                        bibElems.insert(bibElems.end(), bibElem);
                        bibElem.attributes.clear();
                    }
                    allStyles.insert(allStyles.end(), style);
                    std::cout << "ID " << group[2] << std::endl << "Style " << group[1] << std::endl << std::endl;
                    bibElem.id = group[2];
                    bibElem.style = group[1];
                }
                else {
                    styleMatch = false;
                }
                style.clear();
            //}
        }
        if(!line.empty()) {
            style.insert(style.end(), line);
        }
        if(std::regex_search(line, group, fieldExpr) && styleMatch) {
            fieldName = group[1];
            boost::trim(fieldName);
            //fieldName.erase(remove(fieldName.begin(), fieldName.end(), ' '), fieldName.end());
            //std::cout << "typ " << group[1] << std::endl << "inhalt " << group[2] << std::endl << std::endl;
            if (std::find(targetStructure->requiredFields.begin(), targetStructure->requiredFields.end(), fieldName) != targetStructure->requiredFields.end()
            || std::find(targetStructure->optionalFields.begin(), targetStructure->optionalFields.end(), fieldName) != targetStructure->optionalFields.end()) {
                std::cout << "typ " << fieldName << std::endl << "inhalt " << group[2] << std::endl << std::endl;
                field.name = fieldName;
                field.value = group[2];
                bibElem.attributes.insert(bibElem.attributes.end(), field);
            }
        }
    }
    if(styleMatch) {
        allStyles.insert(allStyles.end(), style);
    }
    bibElems.insert(bibElems.end(), bibElem);
    std::cout << "name " << bibElems[1].attributes[1].name << std::endl << "value " << bibElems[1].attributes[1].value << std::endl << std::endl;
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