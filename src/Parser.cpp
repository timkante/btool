#include "Parser.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <regex>
//#include "FileGenerator.hpp"

Parser::Parser(std::string ruleFile, const std::string targetStyle, TranslationTable translationTable)
        : ruleFile(std::move(ruleFile)), targetStyle(std::move(targetStyle)), translationTable(translationTable) {};

void Parser::generate(const std::string sorting, const std::string format) {
    //FileGenerator outputfile = new FileGenerator(parsedElements, format, sorting);
}

std::vector<BibElement> Parser::parseFile(boost::filesystem::ifstream &fsStream) {
    BibElement bibElem = parseElement("", "", StyleProperties());
    std::vector<BibElement> bibElems = {};
    std::string line;
    std::regex expr{"\\@(.*)\\{(.*)\\,"};
    std::smatch group;
    std::string fieldName;
    std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    int requiredFieldSize = targetStructure->requiredFields.size();
    bool styleMatch = false;
    while (std::getline(fsStream, line)) {
        boost::trim(line);
        if (std::regex_search(line, group, expr)) {
            styleMatch = group[1] == targetStyle;
            if (bibElem.id != "" && styleMatch) {
                if (requiredFieldSize > 0)
                    throw std::invalid_argument("Not all required Fields set in Element with ID: " + bibElem.id);
                bibElems.insert(bibElems.end(), bibElem);
            }
            if (styleMatch) {
                bibElem = parseElement(group[1], group[2], StyleProperties());
                requiredFieldSize = targetStructure->requiredFields.size();
            } else {
                continue;
            }

        } else if (styleMatch) {
            Field field = parseField(line, targetStructure, (int &) requiredFieldSize);
            if (field.name != "") {
                bibElem.attributes.insert(bibElem.attributes.end(), field);
            }
        }
    }
    if (requiredFieldSize > 0)
        throw std::invalid_argument("Not all required Fields set in Element with ID: " + bibElem.id);
    bibElems.insert(bibElems.end(), bibElem);
    return bibElems;
}

void Parser::parseFiles(const boost::filesystem::path &path) {
    checkFolder(path);

    boost::filesystem::directory_iterator it{path};
    bool bibFound = false;
    while (it != boost::filesystem::directory_iterator{}) {
        std::string fileExt = boost::filesystem::extension(*it);
        if (fileExt.compare(".bib") == 0) {
            bibFound = true;
            boost::filesystem::ifstream in(*it);
            parseFile(in);
        }
        *it++;
    }
    if (!bibFound) {
        std::cout << "Keine Bib Files im Pfad gefunden!\n";
        std::cout << path.string() << std::endl;
    }
}

Field Parser::parseField(std::string field, std::optional<StyleProperties> targetStructure, int& requiredFieldSize) {
    std::regex fieldExpr{"^\\s*(.*)\\s+=\\s+\\{*(.*?)\\}*\\,?$"};
    std::smatch group;
    if (std::regex_search(field, group, fieldExpr)) {

        std::string fieldName = group[1];
        boost::trim(fieldName);

        if (std::find(targetStructure->requiredFields.begin(), targetStructure->requiredFields.end(), fieldName) !=
            targetStructure->requiredFields.end()){
            requiredFieldSize--;
            return Field(fieldName, replaceUmlaut(group[2]));
        }
            if(std::find(targetStructure->optionalFields.begin(), targetStructure->optionalFields.end(), fieldName) !=
               targetStructure->optionalFields.end()) {
            return Field(fieldName, replaceUmlaut(group[2]));
        }
    }
    return Field("", "");
}

BibElement Parser::parseElement(std::string style, std::string id, StyleProperties styleProps) {
    bool styleMatch = style == targetStyle;
    std::vector<Field> fields = {};
    if (styleMatch) {
        BibElement bibElem = BibElement(id, style, fields);
        return bibElem;
    } else {
        styleMatch = false;
    }
    return BibElement("", "", fields);
}

void Parser::checkFolder(const boost::filesystem::path &path) {
    if (!boost::filesystem::is_directory(path)) {
        throw std::invalid_argument("No Folder!");
    }
}


std::string Parser::replaceUmlaut(std::string line) {
    std::regex expr{"(\\{.*?\\})"};
    std::smatch group;
    std::string value = line;
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> tokenIterator(line.begin(), line.end(), expr);
    if (std::regex_search(value, group, expr)) {
        while (tokenIterator != rend) {
            std::string toConvert = (*tokenIterator).str();
            std::string umlaut = convertUmlaut(toConvert);
            std::size_t pos = value.find(toConvert);

            if (pos != std::string::npos) {
                value.replace(pos, toConvert.length(), umlaut);
            }

            *tokenIterator++;
        }
    }
    return value;
}

std::string Parser::convertUmlaut(std::string toConvert) {
    if (toConvert == "{\\\"a}")
        return "ä";
    if (toConvert == "{\\\"o}")
        return "ö";
    if (toConvert == "{\\\"u}")
        return "ü";
    if (toConvert == "{\\ss}")
        return "ß";
    if (toConvert == "{\\\'a}")
        return "á";
    if (toConvert == "{\\\'e}")
        return "é";

    throw std::invalid_argument("no valid Umlaut: " + toConvert);
}