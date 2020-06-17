#ifndef BIBPARSER_FIELD_HPP
#define BIBPARSER_FIELD_HPP

#include <string>

struct Field {
    std::string name;
    std::string value;

    Field(std::string name, std::string value);
};

#endif
