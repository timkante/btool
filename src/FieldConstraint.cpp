#include "FieldConstraint.hpp"
#include <regex>

FieldConstraint::FieldConstraint(std::string fieldName, std::string fieldFormat) {
    name = fieldName;
    format = fieldFormat; // Datentyp zu regex ändern?
}

bool FieldConstraint::matchesRegex(std::string dataFormat, std::string fieldFormat) {
    if (dataFormat == fieldFormat)
        return true;
    else
        return false;
}

bool FieldConstraint::matchesConstraint(std::string value, Field field) {
    if (field.name == name) {
        if (matchesRegex(value, format))
            return true;
        else
            return false;
    }
}



