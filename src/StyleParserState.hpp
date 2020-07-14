#ifndef BIBPARSER_STYLEPARSERSTATE_HPP
#define BIBPARSER_STYLEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

class StyleParserState : public AbstractParserState {
    std::string style;

public:
    StyleParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
