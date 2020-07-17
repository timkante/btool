#include <boost/filesystem/path.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <spdlog/spdlog.h>
#include <Parser.hpp>
#include <algorithm>
#include <numeric>

using namespace std::literals::string_literals;

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
auto Parser::generate(
    const boost::filesystem::path &inputPath,
    const std::string &sorting
) const noexcept -> std::vector<BibElement> {
  if (!boost::filesystem::exists(inputPath)) {
    spdlog::critical("No such file or directory. [input={}]", inputPath.string());
    return {};
  } else if (boost::filesystem::is_directory(inputPath)) {
    std::vector<BibElement> collector{};
    for (const auto &file : boost::filesystem::directory_iterator(inputPath)) {
      spdlog::info("Parsing File: {} ...", file.path().string());
      std::ifstream inFile{file.path().string()};
      inFile >> std::noskipws;
      std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
      for (const auto &element : generate(std::string_view(inContent), sorting, inputPath.string())) {
        collector.push_back(element);
      }
    }
    return collector;
  } else if (boost::filesystem::is_regular_file(inputPath)) {
    spdlog::info("Parsing File: {} ...", inputPath.string());
    std::ifstream inFile{inputPath.string()};
    std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
    return generate(std::string_view(inContent), sorting, inputPath.string());
  } else {
    spdlog::critical("Unexpected file-descriptor. [input={}]", inputPath.string());
    return {};
  }
}

/**
 * Generate bib-elements and Filter them for a Style
 * @param inputFileContent content of a input-file
 * @param sorting the style name to sort parsing-results for
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed, sorted and filtered bib-elements
 */
auto Parser::generate(
    std::string_view inputFileContent,
    const std::string &sorting,
    const std::string &filename
) const noexcept -> std::vector<BibElement> {
  const auto targetStructure = translationTable.stylePropertiesOf(targetStyle);
  if (!targetStructure) {
    return {};
  } else {
    const auto parsedElements = Parser::elementsOf(inputFileContent, filename);
    std::vector<BibElement> filteredElements{};
    std::copy_if(std::cbegin(parsedElements),
                 std::cend(parsedElements),
                 std::back_inserter(filteredElements),
                 [&](const BibElement &element) {
                   return element.style == targetStyle
                       && element.isCompliantTo(targetStructure.value());
                 }
    );
    std::sort(std::begin(filteredElements),
              std::end(filteredElements),
              [&sorting](const BibElement &l, const BibElement &r) {
                return l.findAttribute(sorting).value_or<Field>({""s, ""s}).value
                    < r.findAttribute(sorting).value_or<Field>({""s, ""s}).value;
              });
    return filteredElements;
  }
}

/**
 * Parse Bib-Elements from a source-file
 * @param input the contents of the source-file
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed bib-elements
 */
auto Parser::elementsOf(
    std::string_view input,
    const std::string &filename
) noexcept -> std::vector<BibElement> {
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
