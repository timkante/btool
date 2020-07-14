#ifndef BIBPARSER_FIELD_HPP
#define BIBPARSER_FIELD_HPP

#include <string>
#include <iostream>

/**
 * Stores information of a Field of a bib-element
 * @brief Field-Container
 */
struct Field {
    std::string name; ///< the name of the Field
    std::string value; ///< the value of the Field

    Field(std::string name, std::string value);

    auto operator==(const Field &other) const noexcept -> bool;
};

auto operator<<(std::ostream &os, Field const &field) -> std::ostream &;

#endif
