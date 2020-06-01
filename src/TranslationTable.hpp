//
// Created by Tim Kante on 01.06.20.
//

#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>

class TranslationTable {
private:
    boost::property_tree::ptree contents;
public:
    explicit TranslationTable(const std::string& fileName);
};

#endif //BIBPARSER_TRANSLATIONTABLE_HPP
