#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <vector>

struct StyleProperties {
    std::string name = "";
    std::vector<std::string> requiredFields = {};
    std::vector<std::string> optionalFields = {};

    StyleProperties() = default;

    StyleProperties(std::string name,
                    std::vector<std::string> requiredFields,
                    std::vector<std::string> optionalFields);

    auto operator==(const StyleProperties &other) const -> bool;
};

#endif
