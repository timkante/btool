#include "FieldConstraint.hpp"
#include <regex>

FieldConstraint::FieldConstraint(std::string fieldName, std::string fieldFormat)
        : name{std::move(fieldName)}, format{std::move(fieldFormat)} {}

bool FieldConstraint::matchesRegex(const std::string &dataFormat, const std::string &fieldFormat) const {
    if (dataFormat == fieldFormat)
        return true;
    else
        return false;
}

bool FieldConstraint::matchesConstraint(const std::string &value, Field field) const {
    if (field.name == name) {
        if (matchesRegex(value, format))
            return true;
        else
            return false;
    }
}
