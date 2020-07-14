#include "KeyParserState.hpp"
#include <boost/algorithm/string.hpp>
#include <GlobalParserState.hpp>
#include <ValueParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

KeyParserState::KeyParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

auto KeyParserState::handleCharacter(const char c) -> ParserState * {
    if (c == '=') {
        if (key.empty()) {
            fail("Key must not be empty"s);
        } else {
            result.back().attributes.emplace_back(boost::trim_copy(key), "");
            const auto valueState = new ValueParserState{context, result};
            delete this;
            return valueState;
        }
    } else if (c == '}') {
        const auto globalState = new GlobalParserState{context, result};
        delete this;
        return globalState;
    } else if (std::isgraph(c)) {
        key += c;
    } else if (!std::isspace(c)) {
        fail("Invalid Character in Key, got so far: ["s + key + "]"s);
    }
    return this;
}
