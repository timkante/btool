#include "GlobalParserState.hpp"
#include <AbstractParserState.hpp>

GlobalParserState::GlobalParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

ParserState *GlobalParserState::handleCharacter(const char c) {
    if (c == '@') {
        auto const nextState = new StyleParserState{context, result};
        delete this;
        return nextState;
    } else {
        return this;
    }
}
