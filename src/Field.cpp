#include <Field.hpp>
#include <utility>

Field::Field(std::string name, std::string value)
        : name{std::move(name)}, value{std::move(value)} {}

auto Field::operator==(const Field &other) const noexcept -> bool {
    return name == other.name && value == other.value;
}

auto operator<<(std::ostream &os, Field const &field) -> std::ostream & {
    return os << "(name=" << field.name << ", value=" << field.value << ")";
}