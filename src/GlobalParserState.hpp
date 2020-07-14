#ifndef BIBPARSER_GLOBALPARSERSTATE_HPP
#define BIBPARSER_GLOBALPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <StyleParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>

/**
 * Global State of the Parser, looking for the next Element to parse (beginning with an '@')
 *
 * @brief Global Parser State
 * @extends AbstractParserState
 */
class GlobalParserState : public AbstractParserState {
public:

    /**
     * Constructor.
     * @param context of the parser
     * @param result accumulator of parsing-results
     */
    GlobalParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    /**
     * Handles the next character in global-state
     * @param c the next character to parse
     * @return a new parser-state
     * @throws ParserException on parsing-error (invalid input)
     */
    auto handleCharacter(char c) -> ParserState * override;
};

#endif
