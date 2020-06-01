//
// Created by Tim Kante on 01.06.20.
//

#include "TranslationTable.hpp"
#include <boost/property_tree/json_parser.hpp>

TranslationTable::TranslationTable(const std::string& fileName) {
    boost::property_tree::read_json(fileName, contents);
}
