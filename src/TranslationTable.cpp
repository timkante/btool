#include <TranslationTable.hpp>
#include <FieldConstraint.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional/optional.hpp>
#include <optional>
#include <iterator>

TranslationTable::TranslationTable(std::stringstream file) {
    boost::property_tree::read_json(file, contents);
    styleProps = std::vector<StyleProperties>();
    commonProps = parseCommonProperties();
}

TranslationTable::TranslationTable(const boost::filesystem::path &path) {
    boost::property_tree::read_json(path.string(), contents);
    styleProps = std::vector<StyleProperties>();
    commonProps = parseCommonProperties();
}

auto TranslationTable::printAll(std::ostream &out) const -> void {
    boost::property_tree::json_parser::write_json(out, contents);
}

auto TranslationTable::parseCommonProperties() const -> StyleProperties {
    const auto parseConstraintNode = [](const boost::property_tree::ptree &node) {
        assert(std::all_of(std::cbegin(node),
                           std::cend(node),
                           [](const boost::property_tree::ptree::value_type &field) {
                               return field.first.empty();
                           }));
        std::vector<std::optional<FieldConstraint>> resultCollector;
        std::transform(
                std::cbegin(node),
                std::cend(node),
                std::back_inserter(resultCollector),
                [](const boost::property_tree::ptree::value_type &field) -> std::optional<FieldConstraint> {
                    const auto title = field.second.get_child_optional("title");
                    const auto format = field.second.get_child_optional("format");
                    if (title.has_value() && format.has_value()) {
                        return FieldConstraint(title.value().data(), std::regex{format.value().data()});
                    } else {
                        return std::nullopt;
                    }
                });

        std::vector<FieldConstraint> validResults;
        for (auto element : resultCollector){
            if (element.has_value() && !element.value().name.empty())
                validResults.push_back(element.value());
        }
        return validResults;
    };

    const auto requiredFieldsNode = contents.get_child_optional("commonRequiredFields");
    const auto optionalFieldsNode = contents.get_child_optional("commonOptionalFields");

    return StyleProperties("_common",
                           requiredFieldsNode.has_value() ? parseConstraintNode(requiredFieldsNode.value())
                                                          : std::vector<FieldConstraint>{},
                           optionalFieldsNode.has_value() ? parseConstraintNode(optionalFieldsNode.value())
                                                          : std::vector<FieldConstraint>{});
}
