#include <StyleProperties.hpp>
#include <utility>

/**
 * Equality-Operator for two style-properties
 * @param other style-properties to compare with
 * @return weather the two style-properties are deeply equal
 */
auto StyleProperties::operator==(const StyleProperties &other) const noexcept -> bool {
  return name == other.name && requiredFields == other.requiredFields && optionalFields == other.optionalFields;
}
