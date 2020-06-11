#include <TranslationTable.hpp>
#include <FieldConstraint.hpp>
#include <boost/property_tree/json_parser.hpp>

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
    return StyleProperties("_common", std::vector<FieldConstraint>(), std::vector<FieldConstraint>());
}
