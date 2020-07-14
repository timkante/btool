#include <boost/filesystem/path.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <spdlog/spdlog.h>
#include <Parser.hpp>
#include <algorithm>
#include <numeric>

/**
 * Constructor.
 * @param ruleFilePath filepath to the translation-table
 * @param targetStyle the style name to filter parse-results for
 */
Parser::Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(ruleFilePath)) {}

/**
 * Constructor.
 * @param ruleFileContents contents of the translation-table
 * @param targetStyle the style name to filter parse-results for
 */
Parser::Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(std::move(ruleFileContents))) {}

/**
 * Generate bib-elements and Filter them for a Style
 * @param inputPath filepath to a directory of bib-Files or a single bib-File
 * @param sorting the style name to sort parsing-results for
 * @return collection of parsed bib-elements
 */
auto Parser::generate(const boost::filesystem::path &inputPath,
                      const std::string &sorting) const noexcept -> std::vector<BibElement> {
    //TODO: Add handling for multiple files + existence check
    std::ifstream inFile{inputPath.string()};
    std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
    return generate(std::string_view(inContent), sorting, inputPath.string());
}

/**
 * Generate bib-elements and Filter them for a Style
 * @param inputFileContent content of a input-file
 * @param sorting the style name to sort parsing-results for
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed, sorted and filtered bib-elements
 */
auto Parser::generate(std::string_view inputFileContent,
                      const std::string &sorting,
                      const std::string &filename) const noexcept -> std::vector<BibElement> {
    const std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    return Parser::elementsOf(inputFileContent, filename);
}

/**
 * Parse Bib-Elements from a source-file
 * @param input the contents of the source-file
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed bib-elements
 */
auto Parser::elementsOf(std::string_view input, const std::string &filename) noexcept -> std::vector<BibElement> {
    ParserContext context(filename);
    std::vector<BibElement> result;
    try {
        delete std::accumulate<std::string_view::iterator, ParserState *>(
                std::cbegin(input),
                std::cend(input),
                new GlobalParserState{context, result},
                [&context](ParserState *const acc, const char it) -> ParserState * {
                    ++context.column;
                    if (it == '\n') {
                        ++context.line;
                        context.column = 0;
                        return acc;
                    }
                    return acc->handleCharacter(it);
                });
        return result;
    } catch (ParserException &e) {
        spdlog::critical("Parsing failed: {}", e.what());
        delete e.state;
        return {};
    }
}
