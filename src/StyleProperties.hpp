#include "FieldConstraint.hpp"
#include <vector>

#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <FieldConstraint.hpp>

struct StyleProperties {
    std::string name;
    std::vector<FieldConstraint> requiredFields;
    std::vector<FieldConstraint> optionalFields;

    StyleProperties(std::string name,
                    std::vector<FieldConstraint> requiredFields,
                    std::vector<FieldConstraint> optionalFields);
};

#endif
