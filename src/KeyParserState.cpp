#include <KeyParserState.hpp>
#include <boost/algorithm/string.hpp>
#include <GlobalParserState.hpp>
#include <ValueParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

/**
 * Constructor.
 * @param context of the parser
 * @param result accumulator of parsing-results
 */
KeyParserState::KeyParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

/**
 * Handles the next character in key-state
 * @param c the next character to parse
 * @return a new parser-state
 * @throws ParserException on parsing-error (invalid input)
 */
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
    } else if (std::isgraph(c) || std::isspace(c)) {
        key += c;
    } else {
        fail("Invalid Character in Key, got so far: ["s + key + "]"s);
    }
    return this;
}
