#ifndef BIBPARSER_FIELDCONSTRAINT_HPP
#define BIBPARSER_FIELDCONSTRAINT_HPP

#include <string>
#include <Field.hpp>
#include <regex>

struct FieldConstraint {
    std::string name;
    std::regex format;

    FieldConstraint(std::string fieldName, std::regex fieldFormat);

    [[nodiscard]] auto matchedBy(const Field &field) const -> bool;
};

#endif
