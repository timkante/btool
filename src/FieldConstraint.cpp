#include "FieldConstraint.hpp"

FieldConstraint::FieldConstraint(std::string fieldName, std::regex fieldFormat)
    : name(std::move(name)), format(std::move(format)){};

bool FieldConstraint::matchesRegex(const std::string& dataFormat, std::regex fieldFormat) {
    return std::regex_match(dataFormat, fieldFormat);
}

bool FieldConstraint::matchesConstraint(std::string value, Field field) {
    if (field.name == name) {
        return (matchesRegex(field.value, format));
    }
}




