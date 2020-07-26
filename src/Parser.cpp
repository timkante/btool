#include <boost/filesystem/path.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <Parser.hpp>
#include <algorithm>
#include <numeric>

using namespace std::literals::string_literals;

/**
 * Constructor.
 * @param ruleFilePath optional filepath to the translation-table
 * @param targetStyle the style name to filter parse-results for
 * @param allowAll flag to allow every element to get parsed (ignore TranslationTable)
 * @throws boost::property_tree::json_parser_error whenever translationTable is not JSON compliant
 * @throws std::invalid_argument whenever translationTable is no regular file or does not exist
 */
Parser::Parser(
    const std::optional<boost::filesystem::path> &ruleFilePath,
    std::vector<std::string> targetStyles,
    const bool allowAll
) : targetStyles(std::move(targetStyles)),
    translationTable(TranslationTable(ruleFilePath)),
    allowAll{allowAll} {}

/**
 * Constructor.
 * @param ruleFileContents optional contents of the translation-table
 * @param targetStyle the style name to filter parse-results for
 * @param allowAll flag to allow every element to get parsed (ignore TranslationTable)
 * @throws boost::property_tree::json_parser_error whenever translationTable is not JSON compliant
 */
Parser::Parser(
    std::optional<std::stringstream> ruleFileContents,
    std::vector<std::string> targetStyles,
    const bool allowAll
) : targetStyles(std::move(targetStyles)),
    translationTable(TranslationTable(std::move(ruleFileContents))),
    allowAll{allowAll} {}

/**
 * Generate bib-elements and Filter them for a Style
 * @param inputPath filepath to a directory of bib-Files or a single bib-File
 * @param sorting the style name to sort parsing-results for
 * @return collection of parsed bib-elements
 * @throws std::runtime_error on parsing error
 * @throws std::illegal_argument if file is invalid
 */
auto Parser::generate(
    const boost::filesystem::path &inputPath,
    const std::optional<std::string> &sorting
) const -> std::vector<BibElement> {
  if (!boost::filesystem::exists(inputPath)) {
    throw std::invalid_argument("No such file or directory. [path=" + inputPath.string() + "]");
  } else if (boost::filesystem::is_directory(inputPath)) {
    std::vector<BibElement> collector{};
    for (const auto &file : boost::filesystem::directory_iterator(inputPath)) {
      std::ifstream inFile{file.path().string()};
      inFile >> std::noskipws;
      std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
      for (const auto &element : generate(std::string_view(inContent), sorting, inputPath.string())) {
        collector.push_back(element);
      }
    }
    if (sorting) sortElements(collector, sorting.value());
    return collector;
  } else if (boost::filesystem::is_regular_file(inputPath)) {
    std::ifstream inFile{inputPath.string()};
    inFile >> std::noskipws;
    std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
    auto elements = generate(std::string_view(inContent), sorting, inputPath.string());
    if (sorting) sortElements(elements, sorting.value());
    return elements;
  } else {
    throw std::invalid_argument("Unexpected file-descriptor. [path=" + inputPath.string() + "]");
  }
}

/**
 * Generate bib-elements and Filter them for a Style
 * @param inputFileContent content of a input-file
 * @param sorting the style name to sort parsing-results for
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed, sorted and filtered bib-elements
 * @throws std::runtime_error on parsing error
 */
auto Parser::generate(
    std::string_view inputFileContent,
    const std::optional<std::string> &sorting,
    const std::string &filename
) const -> std::vector<BibElement> {
  const std::vector<StyleProperties> targetStructures = translationTable.stylePropertiesOf(targetStyles);
  std::vector<BibElement> parsedElements = Parser::elementsOf(inputFileContent, filename);
  if (allowAll) {
    if (sorting) sortElements(parsedElements, sorting.value());
    return parsedElements;
  } else if (targetStructures.empty()) {
    return {};
  } else {
    auto filteredElements = filterElements(parsedElements, targetStructures);
    if (sorting) sortElements(filteredElements, sorting.value());
    return filteredElements;
  }
}

/**
 * Parse Bib-Elements from a source-file
 * @param input the contents of the source-file
 * @param filename name or path of the parsed file (for logging errors)
 * @return collection of parsed bib-elements
 * @throws std::runtime_error if parsing failed
 */
auto Parser::elementsOf(
    std::string_view input,
    const std::string &filename
) -> std::vector<BibElement> {
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
    delete e.state;
    throw std::runtime_error(e.what());
  }
}

/**
 * Sorts a vector of bibElements
 * @param elements[out] the vector of bibElements
 * @param sorting the attribute to sort for
 */
auto Parser::sortElements(std::vector<BibElement> &elements, const std::string &sorting) noexcept -> void {
  std::sort(
      std::begin(elements),
      std::end(elements),
      [&sorting](const BibElement &l, const BibElement &r) {
        return l.findAttribute(sorting).value_or<Field>({""s, ""s}).value
            < r.findAttribute(sorting).value_or<Field>({""s, ""s}).value;
      }
  );
}

/**
 * Generates Elements of multiple input-files
 * @param inputPaths all theinput-paths
 * @param sorting optional sorting to use
 * @return optionally sorted elements
 * @throws std::runtime_error on parsing-error
 * @throws std::invalid_argument if a file is invalid
 */
auto Parser::generate(
    const std::vector<boost::filesystem::path> &inputPaths,
    const std::optional<std::string> &sorting
) const -> std::vector<BibElement> {
  std::vector<BibElement> parsedElements;
  std::for_each(
      std::cbegin(inputPaths),
      std::cend(inputPaths),
      [this, &parsedElements, &sorting](const boost::filesystem::path &p) {
        const auto elements = generate(p, sorting);
        parsedElements.insert(std::end(parsedElements), std::cbegin(elements), std::cend(elements));
      }
  );
  if (sorting) sortElements(parsedElements, sorting.value());
  return parsedElements;
}

/**
 * Filters list of elements for only elements that are compliant to one of a list of properties
 * @param elements the list of elements to filter
 * @param props the list of properties to filter for
 * @return the filtered list of elements
 */
auto Parser::filterElements(
    const std::vector<BibElement> &elements,
    const std::vector<StyleProperties> &props
) noexcept -> std::vector<BibElement> {
  std::vector<BibElement> filteredElements{};
  std::copy_if(
      std::cbegin(elements),
      std::cend(elements),
      std::back_inserter(filteredElements),
      [&props](const BibElement &element) {
        return std::find_if(
            std::cbegin(props),
            std::cend(props),
            [&](const StyleProperties &prop) {
              return element.isCompliantTo(prop);
            }
        ) != std::cend(props);
      }
  );
  return filteredElements;
}