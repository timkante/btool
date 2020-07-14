#ifndef BIBPARSER_KEYPARSERSTATE_HPP
#define BIBPARSER_KEYPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

class KeyParserState : public AbstractParserState {
    std::string key;

public:
    KeyParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
