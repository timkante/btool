#include "StyleProperties.hpp"

StyleProperties::StyleProperties(std::string name,
                                 std::vector<std::string> requiredFields,
                                 std::vector<std::string> optionalFields)
        : name{std::move(name)},
          requiredFields{std::move(requiredFields)},
          optionalFields{std::move(optionalFields)} {}

StyleProperties::StyleProperties() : name{""}, requiredFields{}, optionalFields{} {}
