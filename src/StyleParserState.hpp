#ifndef BIBPARSER_STYLEPARSERSTATE_HPP
#define BIBPARSER_STYLEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

/**
 * Style State of the Parser, parsing the style of the Bib-Element
 *
 * @brief Style Parser State
 * @extends AbstractParserState
 */
class StyleParserState : public AbstractParserState {
    std::string style; ///< @property a accumulator for style-characters while parsing it

public:

    /**
     * Constructor.
     * @param context of the parser
     * @param result accumulator of parsing-results
     */
    StyleParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    /**
     * Handles the next character in style-state
     * @param c the next character to parse
     * @return a new parser-state
     * @throws ParserException on parsing-error (invalid input)
     */
    auto handleCharacter(char c) -> ParserState * override;
};

#endif
