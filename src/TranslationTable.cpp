#include "TranslationTable.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

TranslationTable::TranslationTable(std::stringstream file) {
    boost::property_tree::read_json(file, this->contents);
}

auto TranslationTable::printAll(std::ostream &out) const -> void {
    boost::property_tree::json_parser::write_json(out, this->contents);
}

TranslationTable::TranslationTable(const boost::filesystem::path &path) {
    boost::property_tree::read_json(path.string(), this->contents);
}
