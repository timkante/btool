#ifndef BIBPARSER_BIBELEMENT_HPP
#define BIBPARSER_BIBELEMENT_HPP

#include <string>
#include <Field.hpp>
#include <vector>

struct BibElement{
    std::string id;
    std::string style;
    std::vector<Field> attributes;

    BibElement(std::string id, std::string style, std::vector<Field> attributes);

    bool isComplete(){
        //TODO - Classes missing
        return false;
    }
};

#endif
