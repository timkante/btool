#include <StyleProperties.hpp>
#include <utility>

StyleProperties::StyleProperties(std::string name,
                                 std::vector<std::string> requiredFields,
                                 std::vector<std::string> optionalFields)
        : name{std::move(name)},
          requiredFields{std::move(requiredFields)},
          optionalFields{std::move(optionalFields)} {}

auto StyleProperties::operator==(const StyleProperties &other) const -> bool {
    return name == other.name && requiredFields == other.requiredFields && optionalFields == other.optionalFields;
}
