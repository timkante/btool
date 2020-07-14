#include "AbstractParserState.hpp"
#include <ParserException.hpp>

AbstractParserState::AbstractParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : context{context}, result{result} {}

[[noreturn]] auto AbstractParserState::fail(const std::string &message) -> void {
    throw ParserException{this, context, message};
}

auto AbstractParserState::handleCharacter(char c) -> ParserState * {
    return this;
}
