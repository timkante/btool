#include <TranslationTable.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional/optional.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iterator>
#include <spdlog/spdlog.h>

/**
 * Constructor.
 * @param file contents of a file
 * @note Will log occurring errors and construct empty `styleProperties`, `contents` is invalid then
 */
TranslationTable::TranslationTable(std::stringstream file) noexcept {
  try {
    boost::property_tree::read_json(file, contents);
    styleProperties = parseStyles();
  } catch (const boost::property_tree::json_parser_error &e) {
    spdlog::critical("Contents are no valid JSON-Format [contents={}]", file.str());
    styleProperties = {};
  }
}

/**
 * Constructor.
 * @param path path to a translation-table json-file
 * @note Will log occurring errors and construct empty `styleProperties`, `contents` is invalid then
 */
TranslationTable::TranslationTable(const boost::filesystem::path &path) noexcept {
  if (!boost::filesystem::exists(path)) {
    spdlog::critical("No such file. [translationTablePath={}]", path.string());
    styleProperties = {};
  } else if (!boost::filesystem::is_regular_file(path)) {
    spdlog::critical("Translation-Table is not a file. [translationTablePath={}]", path.string());
    styleProperties = {};
  } else {
    try {
      boost::property_tree::read_json(path.string(), contents);
      styleProperties = parseStyles();
    } catch (const boost::property_tree::json_parser_error &e) {
      spdlog::critical("Contents are no valid JSON-Format [contents={}]", path.string());
      styleProperties = {};
    }
  }
}

/**
 * Prints the content of contents
 * @param[out] out the ostream to print into
 */
auto TranslationTable::printAll(std::ostream &out) const -> void {
  boost::property_tree::json_parser::write_json(out, contents);
}

/**
 * Parses a style from the styles json-pointer
 * @param style the json-pointer to the style
 * @return the parsed style-properties
 */
auto TranslationTable::parseStyle(
    const boost::property_tree::ptree &style
) noexcept -> StyleProperties {
  const auto parseConstraintNode = [](const boost::property_tree::ptree &node) {
    std::unordered_set<std::string> fields;
    std::for_each(std::cbegin(node),
                  std::cend(node),
                  [&fields](const boost::property_tree::ptree::value_type &field) {
                    const std::string title = field.second.data();
                    if (!title.empty()) {
                      fields.insert(title);
                    }
                  });
    return fields;
  };

  const boost::optional<const boost::property_tree::ptree &> name =
      style.get_child_optional("name");
  const boost::optional<const boost::property_tree::ptree &> requiredFieldsNode =
      style.get_child_optional("requiredFields");
  const boost::optional<const boost::property_tree::ptree &> optionalFieldsNode =
      style.get_child_optional("optionalFields");

  return {name ? std::string{name.value().data()} : "",
          requiredFieldsNode ? parseConstraintNode(requiredFieldsNode.value())
                             : std::unordered_set<std::string>{},
          optionalFieldsNode ? parseConstraintNode(optionalFieldsNode.value())
                             : std::unordered_set<std::string>{}};
}

/**
 * Parses Styles of a top-level json-pointer (tree according to proposed structure)
 * @return all the parsed style properties
 */
auto TranslationTable::parseStyles() const noexcept -> std::vector<StyleProperties> {
  std::vector<StyleProperties> props;
  const boost::optional<const boost::property_tree::ptree &> styles =
      contents.get_child_optional("styles");
  if (styles) {
    std::transform(std::cbegin(styles.value()),
                   std::cend(styles.value()),
                   std::back_inserter(props),
                   [this](const boost::property_tree::ptree::value_type &style) {
                     return this->parseStyle(style.second);
                   });
  } else {
    spdlog::critical("Property \"styles\" not found in provided Translation-Table.");
  }
  return props;
}

/**
 * Provides all parsed style-properties
 * @return all parsed style-properties
 */
auto TranslationTable::getStyleProperties() const noexcept -> const std::vector<StyleProperties> & {
  return styleProperties;
}

/**
 * Provides style-properties for a specific style
 * @param name the style name to get properties for
 * @return (maybe) the properties for the style - None if there are none
 */
auto TranslationTable::stylePropertiesOf(
    const std::string &name
) const noexcept -> std::optional<StyleProperties> {
  const auto propItr = std::find_if(std::cbegin(styleProperties), std::cend(styleProperties),
                                    [&name](const StyleProperties &prop) { return prop.name == name; });
  return (propItr != std::cend(styleProperties)) ? std::optional(*propItr) : std::nullopt;
}

/**
 * Provides style-properties for a collection of styles
 * @param names the style names to get properties for
 * @return collection of properties
 * @note if names is empty, returns all properties
 */
auto TranslationTable::stylePropertiesOf(
    const std::vector<std::string> &names
) const noexcept -> std::vector<StyleProperties> {
  if (names.empty()) return getStyleProperties();
  std::vector<StyleProperties> result;
  for (const auto &style : names){
    const auto props = stylePropertiesOf(style);
    if (props) result.push_back(props.value());
  }
  return result;
}