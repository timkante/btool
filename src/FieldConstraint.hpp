#ifndef BIBPARSER_FIELDCONSTRAINT_HPP
#define BIBPARSER_FIELDCONSTRAINT_HPP

#include <string>
#include <Field.hpp>

struct FieldConstraint {
    std::string name;
    std::string format;

    FieldConstraint(std::string fieldName, std::string fieldFormat);

    auto matchesConstraint(const std::string &value, Field field) const -> bool;

    auto matchesRegex(const std::string &dataFormat, const std::string &fieldFormat) const -> bool;
};

#endif
