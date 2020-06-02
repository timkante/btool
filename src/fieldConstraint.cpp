//
// Created by Saskia, Rashid on 02.06.2020.
//

#include "fieldConstraint.h"
#include <regex>

using namespace std;

fieldConstraint::fieldConstraint(String fieldName, String fieldFormat) {
    name = fieldName;
    format = fieldFormat; // Datentyp zu regex ändern?
};


bool matchesRegex(String dataFormat, String fieldFormat) {
    if (regex_match(dataFormat,fieldFormat))
        return true;
    else
        return false;
}

bool matchesConstraint(String value, Field field) {
    if (field.name == name) {
        if (matchesRegex(value, format))
            return true;
        else
            return false;
    };
}



