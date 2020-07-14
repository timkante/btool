#include <StyleParserState.hpp>
#include <boost/algorithm/string.hpp>
#include <IdentifierParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

/**
 * Constructor.
 * @param context of the parser
 * @param result accumulator of parsing-results
 */
StyleParserState::StyleParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
        : AbstractParserState{context, result} {}

/**
 * Handles the next character in style-state
 * @param c the next character to parse
 * @return a new parser-state
 * @throws ParserException on parsing-error (invalid input)
 */
auto StyleParserState::handleCharacter(const char c) -> ParserState * {
    if (c == '{') {
        if (style.empty()) {
            fail("Style-Name must not be empty"s);
        } else {
            result.push_back({"", boost::trim_copy(style), {}});
            const auto identifierState = new IdentifierParserState{context, result};
            delete this;
            return identifierState;
        }
    } else if (std::isgraph(c)) {
        style += c;
        return this;
    } else {
        fail("Invalid Character in Style-Name, got so far: ["s + style + "]"s);
    }
}
