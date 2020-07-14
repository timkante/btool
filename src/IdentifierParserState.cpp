#include <IdentifierParserState.hpp>
#include <boost/algorithm/string.hpp>
#include <KeyParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

/**
 * Constructor.
 * @param context of the parser
 * @param result accumulator of parsing-results
 */
IdentifierParserState::IdentifierParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}


/**
 * Handles the next character in identifier-state
 * @param c the next character to parse
 * @return a new parser-state
 * @throws ParserException on parsing-error (invalid input)
 */
auto IdentifierParserState::handleCharacter(const char c) -> ParserState * {
    if (c == ',') {
        if (identifier.empty()) {
            fail("Identifier must not be empty"s);
        } else {
            result.back().id = boost::trim_copy(identifier);
            const auto keyState = new KeyParserState{context, result};
            delete this;
            return keyState;
        }
    } else if (std::isgraph(c)) {
        identifier += c;
        return this;
    } else {
        fail("Invalid Character in Identifier, got so far: ["s + identifier + "]"s);
    }
}
