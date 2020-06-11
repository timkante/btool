#ifndef BIBPARSER_FIELDCONSTRAINT_HPP
#define BIBPARSER_FIELDCONSTRAINT_HPP

#include <string>
#include <Field.hpp>
#include <regex>

struct FieldConstraint {
    std::string name;
    std::regex format;

    FieldConstraint(std::string fieldName, std::regex fieldFormat);

    auto matchesConstraint(const std::string &value, const Field &field) const -> bool;

    static auto matchesRegex(const std::string &dataFormat, const std::regex& fieldFormat) -> bool;
};

#endif
