#ifndef BIBPARSER_IDENTIFIERPARSERSTATE_HPP
#define BIBPARSER_IDENTIFIERPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

/**
 * Identifier State of the Parser, parsing the identifier of the Bib-Element
 *
 * @brief Identifier Parser State
 */
class IdentifierParserState : public AbstractParserState {
    std::string identifier; ///< @property a accumulator for identifier-characters while parsing it

public:

    /**
     * Constructor.
     * @param context of the parser
     * @param result accumulator of parsing-results
     */
    IdentifierParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    /**
     * Handles the next character in identifier-state
     * @param c the next character to parse
     * @return a new parser-state
     * @throws ParserException on parsing-error (invalid input)
     */
    auto handleCharacter(char c) -> ParserState * override;
};

#endif
