#include "ValueParserState.hpp"
#include <boost/algorithm/string.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <KeyParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

ValueParserState::ValueParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

auto ValueParserState::handleCharacter(const char c) -> ParserState * {
    if (c == ',') {
        if (value.empty()) {
            fail("Key must not be empty"s);
        } else if (braces.empty()) {
            result.back().attributes.back().value = boost::trim_copy(value);
            const auto keyState = new KeyParserState{context, result};
            delete this;
            return keyState;
        } else {
            value += c;
        }
    } else if (c == '{') {
        value += c;
        braces.push(std::make_pair(context.line, context.column));
    } else if (c == '}') {
        if (braces.empty()){
            result.back().attributes.back().value = boost::trim_copy(value);
            const auto keyState = new GlobalParserState{context, result};
            delete this;
            return keyState;
        } else {
            value += c;
            braces.pop();
        }
    } else if (std::isgraph(c) || std::isspace(c)) {
        value += c;
    } else {
        fail("Invalid Character in Value, got so far: ["s + value + "]"s);
    }
    return this;
}
