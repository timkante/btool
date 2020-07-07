#include <TranslationTable.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional/optional.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iterator>
#include <spdlog/spdlog.h>

TranslationTable::TranslationTable(std::stringstream file) {
    try {
        boost::property_tree::read_json(file, contents);
        styleProperties = parseStyles();
    } catch (const boost::property_tree::json_parser_error &e) {
        spdlog::critical("Contents are no valid JSON-Format [contents={}]", file.str());
        styleProperties = {};
    }
}

TranslationTable::TranslationTable(const boost::filesystem::path &path) {
    if (!boost::filesystem::exists(path)){
        spdlog::critical("No such file. [translationTablePath={}]", path.string());
        styleProperties = {};
    } else if (!boost::filesystem::is_regular_file(path)){
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

auto TranslationTable::printAll(std::ostream &out) const -> void {
    boost::property_tree::json_parser::write_json(out, contents);
}

auto TranslationTable::parseStyle(const boost::property_tree::ptree &style) -> StyleProperties {
    const auto parseConstraintNode = [](const boost::property_tree::ptree &node) {
        std::vector<std::string> fields;
        std::for_each(std::cbegin(node),
                      std::cend(node),
                      [&fields](const boost::property_tree::ptree::value_type &field) {
                          const std::string title = field.second.data();
                          if (!title.empty()) {
                              fields.emplace_back(title);
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

    return StyleProperties(name ? std::string{name.value().data()} : "",
                           requiredFieldsNode ? parseConstraintNode(requiredFieldsNode.value())
                                              : std::vector<std::string>{},
                           optionalFieldsNode ? parseConstraintNode(optionalFieldsNode.value())
                                              : std::vector<std::string>{});
}

auto TranslationTable::parseStyles() const -> std::vector<StyleProperties> {
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

auto TranslationTable::getStyleProperties() const -> const std::vector<StyleProperties> & {
    return styleProperties;
}

auto TranslationTable::stylePropertiesOf(const std::string &name) const -> std::optional<StyleProperties> {
    const auto propItr = std::find_if(std::cbegin(styleProperties), std::cend(styleProperties),
                                      [&name](const StyleProperties &prop) { return prop.name == name; });
    return (propItr != std::cend(styleProperties)) ? std::optional(*propItr) : std::nullopt;
}
