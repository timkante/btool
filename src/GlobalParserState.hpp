#ifndef BIBPARSER_GLOBALPARSERSTATE_HPP
#define BIBPARSER_GLOBALPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <StyleParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>

/**
 * Global State of the Parser, looking for the next Element to parse (beginning with an '@')
 * @brief Global Parser State
 */
class GlobalParserState : public AbstractParserState {
public:

    GlobalParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
