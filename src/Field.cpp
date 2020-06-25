#include <Field.hpp>
#include <utility>

Field::Field(std::string name, std::string value)
        : name{std::move(name)}, value{std::move(value)} {}
