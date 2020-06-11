#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <sstream>
#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include <StyleProperties.hpp>

class TranslationTable {
private:
    boost::property_tree::ptree contents;

    auto parseCommonProperties() const -> StyleProperties;

public:
    std::vector<StyleProperties> styleProps;
    StyleProperties commonProps;

    explicit TranslationTable(std::stringstream file);

    explicit TranslationTable(const boost::filesystem::path &path);

    auto printAll(std::ostream &out = std::cout) const -> void;
};

#endif
