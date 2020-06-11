#include "FieldConstraint.hpp"

FieldConstraint::FieldConstraint(std::string fieldName, std::regex fieldFormat)
        : name{std::move(fieldName)}, format{std::move(fieldFormat)} {}

bool FieldConstraint::matchesRegex(const std::string &dataFormat, const std::regex &fieldFormat) {
    return std::regex_match(dataFormat, fieldFormat);
}

bool FieldConstraint::matchesConstraint(const std::string &value, const Field &field) const {
    return field.name == name && matchesRegex(field.value, format);
}
