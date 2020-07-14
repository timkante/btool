#include <StyleProperties.hpp>
#include <utility>

/**
 * Constructor.
 * @param name name of the style
 * @param requiredFields all the required fields
 * @param optionalFields all the optional fields
 */
StyleProperties::StyleProperties(std::string name,
                                 std::vector<std::string> requiredFields,
                                 std::vector<std::string> optionalFields)
        : name{std::move(name)},
          requiredFields{std::move(requiredFields)},
          optionalFields{std::move(optionalFields)} {}

/**
 * Equality-Operator for two style-properties
 * @param other style-properties to compare with
 * @return weather the two style-properties are deeply equal
 */
auto StyleProperties::operator==(const StyleProperties &other) const noexcept -> bool {
    return name == other.name && requiredFields == other.requiredFields && optionalFields == other.optionalFields;
}
