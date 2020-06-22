#ifndef BIBPARSER_PARSER_HPP
#define BIBPARSER_PARSER_HPP
#include <TranslationTable.hpp>
#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <boost/filesystem.hpp>
#include <Field.hpp>
#include <vector>
#include <string>

class Parser {
private:
    std::vector<BibElement> parsedElements;
    std::string ruleFile;
    std::string targetStyle;
    TranslationTable translationTable;
public:
    Parser(std::string ruleFile, std::string targetStyle, TranslationTable translationTable);
    void generate(std::string sorting, std::string format);
    std::vector<BibElement> parseFile(boost::filesystem::ifstream &fsStream);
    void parseFiles(const boost::filesystem::path& path);
    Field parseField(std::string field, StyleProperties checkAgainst);
    BibElement parseElement(std::string element, StyleProperties styles);
};

#endif
