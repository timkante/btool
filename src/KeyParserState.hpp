#ifndef BIBPARSER_KEYPARSERSTATE_HPP
#define BIBPARSER_KEYPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

/**
 * Key State of the Parser, parsing the next key of the Bib-Elements properties
 *
 * @brief Key Parser State
 */
class KeyParserState : public AbstractParserState {
    std::string key; ///< @property a accumulator for key-characters while parsing it

public:

    /**
     * Constructor.
     * @param context of the parser
     * @param result accumulator of parsing-results
     */
    KeyParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    /**
     * Handles the next character in key-state
     * @param c the next character to parse
     * @return a new parser-state
     * @throws ParserException on parsing-error (invalid input)
     */
    auto handleCharacter(char c) -> ParserState * override;
};

#endif
