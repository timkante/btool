#include "BibElement.hpp"

BibElement::BibElement(std::string id, std::string style, std::vector<Field> attributes)
        : id{std::move(id)}, style{std::move(style)}, attributes{std::move(attributes)} {}

bool BibElement::isComplete() const {
    //TODO - Classes missing
    return false;
}
