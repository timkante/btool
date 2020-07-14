#ifndef BIBPARSER_VALUEPARSERSTATE_HPP
#define BIBPARSER_VALUEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <cctype>
#include <vector>
#include <string>
#include <stack>

/**
 * Value State of the Parser, parsing the value of the last Bib-Elements properties key
 *
 * @brief Key Parser State
 * @extends AbstractParserState
 */
class ValueParserState : public AbstractParserState {
    std::string value; ///< @property a accumulator for value-characters while parsing it
    std::stack<std::pair<std::size_t, std::size_t>> braces; ///< @property a stack for counting delimiting braces

public:

    /**
     * Constructor.
     * @param context of the parser
     * @param result accumulator of parsing-results
     */
    ValueParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    /**
     * Handles the next character in value-state
     * @param c the next character to parse
     * @return a new parser-state
     * @throws ParserException on parsing-error (invalid input)
     */
    auto handleCharacter(char c) -> ParserState * override;
};

#endif
