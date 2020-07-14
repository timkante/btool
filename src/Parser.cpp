#include <boost/filesystem/path.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <spdlog/spdlog.h>
#include <Parser.hpp>
#include <algorithm>
#include <numeric>

Parser::Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(ruleFilePath)) {}

Parser::Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(std::move(ruleFileContents))) {}

auto Parser::generate(const boost::filesystem::path &inputPath,
                      const std::string &sorting) const noexcept -> std::vector<BibElement> {
    std::ifstream inFile{inputPath.string()};
    std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
    return generate(std::string_view(inContent), sorting, inputPath.string());
}

auto Parser::generate(std::string_view inputFileContent,
                      const std::string &sorting,
                      const std::string &filename) const noexcept -> std::vector<BibElement> {
    const std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    return Parser::elementsOf(inputFileContent, filename);
}

auto Parser::elementsOf(std::string_view input, const std::string &filename) -> std::vector<BibElement> {
    ParserContext context(filename);
    std::vector<BibElement> result;
    try {
        delete std::reduce<std::string_view::iterator, ParserState *>(
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
