#ifndef BIBPARSER_FIELDCONSTRAINT_HPP
#define BIBPARSER_FIELDCONSTRAINT_HPP
#include <string>
#include <Field.hpp>

struct FieldConstraint {
    std::string name;
    std::string format;

    FieldConstraint(std::string fieldName, std::string fieldFormat);
    bool matchesConstraint(std::string value, Field field);
    bool matchesRegex(std::string dataFormat, std::string fieldFormat);
};


#endif
