//
// Created by Saskia on 02.06.2020.
//

#include "fieldConstraint.h"
#include <vector>

#ifndef BIBPARSER_STYLEPROPERTIES_H
#define BIBPARSER_STYLEPROPERTIES_H


class styleProperties {
    public:
        String name;
        std::vector<fieldConstraint> requiredFields;
        std::vector<fieldConstraint> optionalFields;
};


#endif //BIBPARSER_STYLEPROPERTIES_H
