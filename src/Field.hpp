#ifndef BIBPARSER_FIELD_HPP
#define BIBPARSER_FIELD_HPP

#include <string>

struct Field {
    std::string name, value;
    bool isRequired;
    Field(std::string name, std::string value, bool isRequired);
};

#endif
