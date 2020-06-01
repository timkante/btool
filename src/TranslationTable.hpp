//
// Created by Tim Kante on 01.06.20.
//

#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>

class TranslationTable {
private:
    boost::property_tree::ptree contents;
public:
    explicit TranslationTable(std::stringstream file);
    explicit TranslationTable(const boost::filesystem::path& path);
    auto printAll() -> std::stringstream;
};

#endif //BIBPARSER_TRANSLATIONTABLE_HPP
