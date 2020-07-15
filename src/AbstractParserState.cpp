#include "AbstractParserState.hpp"
#include <ParserException.hpp>

/**
 * Constructor.
 * @param context the context of the State
 * @param result an accumulator for results
 */
AbstractParserState::AbstractParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
    : context{context}, result{result} {}

/**
 * Error handling on parsing-error
 * @param message Error-Message to display
 * @throws ParserException (always)
 */
[[noreturn]] auto AbstractParserState::fail(const std::string &message) -> void {
  throw ParserException{this, context, message};
}

/**
 * Behaviour of a State to parse next Character
 * @param c the next character
 * @return a new Parser-State
 */
auto AbstractParserState::handleCharacter(char c) -> ParserState * {
  return this;
}
