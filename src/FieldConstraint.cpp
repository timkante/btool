#include "FieldConstraint.hpp"

FieldConstraint::FieldConstraint(std::string fieldName, std::regex fieldFormat) {
    name = fieldName;
    format = fieldFormat; // Datentyp zu regex ändern?
}

bool FieldConstraint::matchesRegex(const std::string& dataFormat, std::regex fieldFormat) {
    return std::regex_match(dataFormat, fieldFormat);
}

bool FieldConstraint::matchesConstraint(std::string value, Field field) {
    if (field.name == name) {
        if (matchesRegex(value, format))
            return true;
        else
            return false;
    }
}




