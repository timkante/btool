#ifndef BIBPARSER_BIBELEMENT_HPP
#define BIBPARSER_BIBELEMENT_HPP

#include <StyleProperties.hpp>
#include <Field.hpp>
#include <string>
#include <vector>

/**
 * Stores information of a bib-element
 * @brief bib-element-Container
 */
struct BibElement {
    std::string id; ///< @property the elements (unique) id
    std::string style; ///< @property the style-name of the element
    std::vector<Field> attributes; ///< @property the attributes of the element

    BibElement(std::string id, std::string style, std::vector<Field> attributes);

    [[nodiscard]] auto isCompliantTo(const StyleProperties &props) const -> bool;

    auto operator==(const BibElement &other) const noexcept -> bool;
};

auto operator<<(std::ostream &os, BibElement const &elem) -> std::ostream &;

#endif
