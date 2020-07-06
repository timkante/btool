#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <vector>

/**
 * Stores information of a styles properties
 *
 * @brief style-properties-container
 */
struct StyleProperties {
    std::string name = ""; ///< @property name of the style
    std::vector<std::string> requiredFields = {}; ///< @property all the required fields
    std::vector<std::string> optionalFields = {}; ///< @property all the optional fields

    /**
     * Default constructor.
     */
    StyleProperties() = default;

    /**
     * Constructor.
     *
     * @param name name of the style
     * @param requiredFields all the required fields
     * @param optionalFields all the optional fields
     */
    StyleProperties(std::string name,
                    std::vector<std::string> requiredFields,
                    std::vector<std::string> optionalFields);

    /**
     * Equality-Operator for two style-properties
     *
     * @param other style-properties to compare with
     * @return weather the two style-properties are deeply equal
     */
    auto operator==(const StyleProperties &other) const -> bool;
};

#endif
