//
// Created by Tim Kante on 14.07.20.
//

#ifndef BIBPARSER_IDENTIFIERPARSERSTATE_HPP
#define BIBPARSER_IDENTIFIERPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

class IdentifierParserState : public AbstractParserState {
    std::string identifier;

public:
    IdentifierParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
