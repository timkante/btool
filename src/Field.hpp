#ifndef BIBPARSER_FIELD_HPP
#define BIBPARSER_FIELD_HPP

#include <string>

/**
 * @brief Stores information of a Field of a bib-Element
 */
struct Field {
    std::string name; ///< @property The name of the Field
    std::string value; ///< @property The value of the Field

    /**
     * @brief Constructor.
     * @param name Name of the Field
     * @param value Value of the Field
     */
    Field(std::string name, std::string value);
};

#endif
