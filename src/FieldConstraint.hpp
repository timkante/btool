#ifndef BIBPARSER_FIELDCONSTRAINT_HPP
#define BIBPARSER_FIELDCONSTRAINT_HPP

#include <string>
#include <Field.hpp>
#include <Regex>

struct FieldConstraint {
    std::string name;
    std::regex format;

    FieldConstraint(std::string fieldName, std::regex fieldFormat);
    bool matchesConstraint(std::string value, Field field);
    bool matchesRegex(const std::string& dataFormat, std::regex fieldFormat);
};

#endif
