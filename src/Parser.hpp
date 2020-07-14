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

    /**
     * Constructor.
     * @param ruleFilePath filepath to the translation-table
     * @param targetStyle the style name to filter parse-results for
     */
    Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept;

    /**
     * Constructor.
     * @param ruleFileContents contents of the translation-table
     * @param targetStyle the style name to filter parse-results for
     */
    Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept;

    /**
     * Generate bib-elements and Filter them for a Style
     * @param inputPath filepath to a directory of bib-Files or a single bib-File
     * @param sorting the style name to sort parsing-results for
     * @return collection of parsed bib-elements
     */
    [[nodiscard]] auto generate(const boost::filesystem::path &inputPath,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;

    /**
     * Generate bib-elements and Filter them for a Style
     * @param inputFileContent content of a input-file
     * @param sorting the style name to sort parsing-results for
     * @param filename name or path of the parsed file (for logging errors)
     * @return collection of parsed, sorted and filtered bib-elements
     */
    [[nodiscard]] auto generate(std::string_view inputFileContent,
                                const std::string &sorting,
                                const std::string &filename) const noexcept -> std::vector<BibElement>;

private:

    /**
     * Parse Bib-Elements from a source-file
     * @param input the contents of the source-file
     * @param filename name or path of the parsed file (for logging errors)
     * @return collection of parsed bib-elements
     */
    static auto elementsOf(std::string_view input, const std::string &filename) noexcept -> std::vector<BibElement>;
};

#endif
