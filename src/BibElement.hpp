#ifndef BIBPARSER_BIBELEMENT_HPP
#define BIBPARSER_BIBELEMENT_HPP

#include <StyleProperties.hpp>
#include <Field.hpp>
#include <string>
#include <vector>

/**
 * Stores information of a bib-element
 *
 * @brief bib-element-Container
 */
struct BibElement {
    std::string id; ///< @property the elements (unique) id
    std::string style; ///< @property the style-name of the element
    std::vector<Field> attributes; ///< @property the attributes of the element

    /**
     * Constructor.
     *
     * @param id (unique) id
     * @param style name of the elements style
     * @param attributes attributes of the element
     */
    BibElement(std::string id, std::string style, std::vector<Field> attributes);

    /**
     * Checks if the bib-element is compliant to given style-properties
     *
     * @param props style-properties to check compliance against
     * @return weather the element is compliant or not
     */
    [[nodiscard]] auto isCompliantTo(const StyleProperties &props) const -> bool;

    /**
     * Equality-Operator for two bib-elements
     *
     * @param other bib-element to compare with
     * @return weather the two bib-elements are deeply equal
     */
    auto operator==(const BibElement &other) const noexcept -> bool;
};

#endif
