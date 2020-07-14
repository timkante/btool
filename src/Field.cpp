#include <Field.hpp>
#include <utility>

/**
 * Constructor.
 * @param name Name of the Field
 * @param value Value of the Field
 */
Field::Field(std::string name, std::string value)
        : name{std::move(name)}, value{std::move(value)} {}

/**
 * Equality-Operator for two fields
 * @param other field to compare with
 * @return weather the two fields are deeply equal
 */
auto Field::operator==(const Field &other) const noexcept -> bool {
    return name == other.name && value == other.value;
}

/**
 * Overload of ostream-operator for Fields
 * @param os ostream reference
 * @param field the field to stream to os
 * @return the ostream reference after streaming the field into it
 */
auto operator<<(std::ostream &os, Field const &field) -> std::ostream & {
    return os << "(name=" << field.name << ", value=" << field.value << ")";
}
