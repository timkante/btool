#ifndef BIBPARSER_BIBELEMENT_HPP
#define BIBPARSER_BIBELEMENT_HPP

#include <Field.hpp>
#include <string>
#include <vector>

struct BibElement {
    std::string id;
    std::string style;
    std::vector<Field> attributes;

    BibElement(std::string id, std::string style, std::vector<Field> attributes);

    [[nodiscard]] auto isComplete() const -> bool;
};

#endif
