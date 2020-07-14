#include <GlobalParserState.hpp>
#include <AbstractParserState.hpp>

/**
 * Constructor.
 * @param context of the parser
 * @param result accumulator of parsing-results
 */
GlobalParserState::GlobalParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

/**
 * Handles the next character in global-state
 * @param c the next character to parse
 * @return a new parser-state
 * @throws ParserException on parsing-error (invalid input)
 */
ParserState *GlobalParserState::handleCharacter(const char c) {
    if (c == '@') {
        auto const nextState = new StyleParserState{context, result};
        delete this;
        return nextState;
    } else {
        return this;
    }
}
