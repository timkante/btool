#include <Field.hpp>

Field::Field(std::string name, std::string value, bool isRequired)
    : name(std::move(name)), value(std::move(value)), isRequired(isRequired){}
