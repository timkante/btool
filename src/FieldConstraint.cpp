#include "FieldConstraint.hpp"

FieldConstraint::FieldConstraint(std::string fieldName, std::regex fieldFormat)
        : name{std::move(fieldName)}, format{std::move(fieldFormat)} {}

bool FieldConstraint::matchedBy(const Field &field) const {
    return field.name == name && std::regex_match(field.value, format);
}

auto FieldConstraint::operator==(const FieldConstraint &other) const -> bool {
    return name == other.name && format.flags() == other.format.flags();
}
