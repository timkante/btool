#ifndef BIBPARSER_PARSER_HPP
#define BIBPARSER_PARSER_HPP

#include <TranslationTable.hpp>
#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <boost/filesystem.hpp>
#include <Field.hpp>
#include <vector>
#include <string>

/**
 * Handles interaction with the bib-files and does parsing of it
 *
 * @brief interface to interact with bib-files
 */
class Parser {
private:
    std::string targetStyle; ///< @property the target-style of the generated files
    TranslationTable translationTable; ///< @property translation-Table handler

    std::string convertUmlaut(std::string toConvert);

    std::string replaceUmlaut(std::string line);

    std::vector<BibElement> parseFile(boost::filesystem::ifstream &fsStream);

    void parseFiles(const boost::filesystem::path &path);

    Field parseField(std::string field, std::optional<StyleProperties> targetStructure, int &requiredFieldSize);

    BibElement parseElement(std::string style, std::string id, StyleProperties styleProps);

public:
    Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept;

    Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept;

    [[nodiscard]] auto generate(const boost::filesystem::path &inputPath,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;

    [[nodiscard]] auto generate(std::stringstream &inputFileContent,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;
};

#endif
