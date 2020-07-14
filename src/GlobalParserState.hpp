#ifndef BIBPARSER_GLOBALPARSERSTATE_HPP
#define BIBPARSER_GLOBALPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <StyleParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>

class GlobalParserState : public AbstractParserState {
public:
    GlobalParserState(
            ParserContext & context,
            std::vector<BibElement> & result
    ) noexcept;

    ParserState * handleCharacter(char c) override;
};

#endif
