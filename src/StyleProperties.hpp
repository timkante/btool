#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <vector>

struct StyleProperties {
    std::string name;
    std::vector<std::string> requiredFields;
    std::vector<std::string> optionalFields;

    StyleProperties();

    StyleProperties(std::string name,
                    std::vector<std::string> requiredFields,
                    std::vector<std::string> optionalFields);
};

#endif
