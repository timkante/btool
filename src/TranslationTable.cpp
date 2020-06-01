//
// Created by Tim Kante on 01.06.20.
//

#include "TranslationTable.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <sstream>

TranslationTable::TranslationTable(std::stringstream file) {
    boost::property_tree::read_json(file, this->contents);
}

auto TranslationTable::printAll() -> std::stringstream {
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, this->contents);
    return ss;
}

TranslationTable::TranslationTable(const boost::filesystem::path& path) {
    boost::property_tree::read_json(path.string(), this->contents);
}
