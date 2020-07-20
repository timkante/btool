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
 * @brief interface to interact with bib-files
 */
class Parser {
  std::vector<std::string> targetStyles; ///< the target-styles of the generated files
  TranslationTable translationTable; ///< translation-Table handler
  bool allowAll; ///< flag that allows all styles and fields to get parsed (set when missing translationTable)

 public:
  Parser(
      const std::optional<boost::filesystem::path> &ruleFilePath,
      std::vector<std::string> targetStyles,
      const bool allowAll = false
  );

  Parser(
      std::optional<std::stringstream> ruleFileContents,
      std::vector<std::string> targetStyle,
      const bool allowAll = false
  );

  [[nodiscard]] auto generate(
      const std::vector<boost::filesystem::path> &inputPaths,
      const std::optional<std::string> &sorting
  ) const -> std::vector<BibElement>;

  [[nodiscard]] auto generate(
      const boost::filesystem::path &inputPath,
      const std::optional<std::string> &sorting
  ) const -> std::vector<BibElement>;

  [[nodiscard]] auto generate(
      std::string_view inputFileContent,
      const std::optional<std::string> &sorting,
      const std::string &filename
  ) const -> std::vector<BibElement>;

 private:

  static auto elementsOf(
      std::string_view input,
      const std::string &filename
  ) -> std::vector<BibElement>;

  static auto sortElements(
      std::vector<BibElement> &elements,
      const std::string &sorting
  ) noexcept -> void;

  static auto filterElements(
      const std::vector<BibElement> &elements,
      const std::vector<StyleProperties> &props
  ) noexcept -> std::vector<BibElement>;
};

#endif
