#include "StyleProperties.hpp"

StyleProperties::StyleProperties(std::string name,
                                 std::vector<FieldConstraint> requiredFields,
                                 std::vector<FieldConstraint> optionalFields)
        : name{std::move(name)},
          requiredFields{std::move(requiredFields)},
          optionalFields{std::move(optionalFields)} {}
