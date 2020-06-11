#include "FieldConstraint.hpp"

bool FieldConstraint::matchesRegex(const std::string& dataFormat, std::regex fieldFormat) {
    return std::regex_match(dataFormat, fieldFormat);
}

FieldConstraint::FieldConstraint(std::string fieldName, std::string fieldFormat)
        : name{std::move(fieldName)}, format{std::move(fieldFormat)} {}

bool FieldConstraint::matchesConstraint(const std::string &value, Field field) const {
    if (field.name == name) {
        return (matchesRegex(field.value, format));
    }
}
