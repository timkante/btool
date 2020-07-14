#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <algorithm>
#include <iostream>
#include <utility>

/**
 * Constructor.
 * @param id (unique) id
 * @param style name of the elements style
 * @param attributes attributes of the element
 */
BibElement::BibElement(std::string id, std::string style, std::vector<Field> attributes)
        : id{std::move(id)}, style{std::move(style)}, attributes{std::move(attributes)} {}

/**
 * Checks if the bib-element is compliant to given style-properties
 * @param props style-properties to check compliance against
 * @return weather the element is compliant or not
 */
auto BibElement::isCompliantTo(const StyleProperties &props) const -> bool {
    return std::all_of(std::cbegin(props.requiredFields),
                       std::cend(props.requiredFields),
                       [this](const std::string &requiredFieldName) {
                           return std::find_if(std::cbegin(this->attributes),
                                               std::cend(this->attributes),
                                               [&requiredFieldName](const Field &actualField) {
                                                   return requiredFieldName == actualField.name;
                                               }) != std::cend(this->attributes);
                       });
}

/**
 * Equality-Operator for two bib-elements
 * @param other bib-element to compare with
 * @return weather the two bib-elements are deeply equal
 */
auto BibElement::operator==(const BibElement &other) const noexcept -> bool {
    return id == other.id && style == other.style && attributes == other.attributes;
}

/**
 * Overload of ostream-operator for BibElement
 * @param os ostream reference
 * @param elem the element to stream to os
 * @return the ostream reference after streaming elem into it
 */
auto operator<<(std::ostream &os, BibElement const &elem) -> std::ostream & {
    os << "(id=" << elem.id << ", style=" << elem.style << ", attributes=[";
    std::for_each(std::cbegin(elem.attributes), std::cend(elem.attributes), [&os](const Field &attribute) {
        os << attribute;
    });
    return os << "])";
}
