#ifndef BIBPARSER_PARSER_HPP
#define BIBPARSER_PARSER_HPP

#include <TranslationTable.hpp>
#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <boost/filesystem.hpp>
#include <Field.hpp>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * Handles interaction with the bib-files and does parsing of it
 *
 * @brief interface to interact with bib-files
 */
class Parser {
    std::string targetStyle; ///< @property the target-style of the generated files
    TranslationTable translationTable; ///< @property translation-Table handler

public:
    Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept;

    Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept;

    [[nodiscard]] auto generate(const boost::filesystem::path &inputPath,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;

    [[nodiscard]] auto generate(std::string_view inputFileContent,
                                const std::string &sorting,
                                const std::string &filename) const noexcept -> std::vector<BibElement>;

private:
    static auto elementsOf(std::string_view input, const std::string &filename) -> std::vector<BibElement>;
};

#endif
