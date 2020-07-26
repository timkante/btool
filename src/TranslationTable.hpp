#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include <StyleProperties.hpp>
#include <optional>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Handles interaction with the translation-table-file and does parsing of it
 * @brief api to interact with translation-table resource
 */
class TranslationTable {
  boost::property_tree::ptree contents; ///< pointer to parsed json-tree
  std::vector<StyleProperties> styleProperties; ///< parsed style-properties
  
  [[nodiscard]] static auto parseStyle(const boost::property_tree::ptree &style) noexcept -> StyleProperties;

  [[nodiscard]] auto parseStyles() const -> std::vector<StyleProperties>;

 public:

  explicit TranslationTable(std::optional<std::stringstream> file);

  explicit TranslationTable(const std::optional<boost::filesystem::path> &path);

  auto printAll(std::ostream &out = std::cout) const -> void;

  [[nodiscard]] auto getStyleProperties() const noexcept -> const std::vector<StyleProperties> &;

  [[nodiscard]] auto stylePropertiesOf(const std::string &name) const noexcept -> std::optional<StyleProperties>;

  [[nodiscard]] auto stylePropertiesOf(
      const std::vector<std::string> &names
  ) const noexcept -> std::vector<StyleProperties>;
};

#endif
