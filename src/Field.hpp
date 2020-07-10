#ifndef BIBPARSER_FIELD_HPP
#define BIBPARSER_FIELD_HPP

#include <string>

/**
 * Stores information of a Field of a bib-element
 *
 * @brief Field-Container
 */
struct Field {
    std::string name; ///< @property the name of the Field
    std::string value; ///< @property the value of the Field

    /**
     * Constructor.
     *
     * @param name Name of the Field
     * @param value Value of the Field
     */
    Field(std::string name, std::string value);

    /**
     * Equality-Operator for two fields
     *
     * @param other field to compare with
     * @return weather the two fields are deeply equal
     */
    auto operator==(const Field &other) const noexcept -> bool;
};

#endif
