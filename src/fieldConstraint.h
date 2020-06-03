//
// Created by Saskia, Rashid on 02.06.2020.
//

#ifndef BIBPARSER_FIELDCONSTRAINT_H
#define BIBPARSER_FIELDCONSTRAINT_H


class fieldConstraint {
    public:
        String name;
        String format;

        fieldConstraint(String fieldName, String fieldFormat);
        bool matchesConstraint(String value, Field field);
        bool matchesRegex(String dataFormat, String fieldFormat);
};


#endif //BIBPARSER_FIELDCONSTRAINT_H
