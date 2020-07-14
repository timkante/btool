#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <algorithm>
#include <iostream>
#include <utility>

BibElement::BibElement(std::string id, std::string style, std::vector<Field> attributes)
        : id{std::move(id)}, style{std::move(style)}, attributes{std::move(attributes)} {}

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

auto BibElement::operator==(const BibElement &other) const noexcept -> bool {
    return id == other.id && style == other.style && attributes == other.attributes;
}

auto operator<<(std::ostream &os, BibElement const &elem) -> std::ostream & {
    os << "(id=" << elem.id << ", style=" << elem.style << ", attributes=[";
    std::for_each(std::cbegin(elem.attributes), std::cend(elem.attributes), [&os](const Field &attribute) {
        os << attribute;
    });
    return os << "])";
}
