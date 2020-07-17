#include <ValueParserState.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <GlobalParserState.hpp>
#include <ParserException.hpp>
#include <KeyParserState.hpp>
#include <string>
#include <cctype>

using namespace std::literals::string_literals;

/**
 * Constructor.
 * @param context of the parser
 * @param result accumulator of parsing-results
 */
ValueParserState::ValueParserState(ParserContext &context, std::vector<BibElement> &result) noexcept
    : AbstractParserState{context, result} {}

/**
 * Handles the next character in value-state
 * @param c the next character to parse
 * @return a new parser-state
 * @throws ParserException on parsing-error (invalid input)
 */
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
    braces.push(std::make_pair(context.line, context.column));
  } else if (c == '}') {
    replaceSpecialCharacter(value);
    if (braces.empty()) {
      result.back().attributes.back().value = boost::trim_copy(value);
      const auto keyState = new GlobalParserState{context, result};
      delete this;
      return keyState;
    } else {
      braces.pop();
    }
  } else if (std::isgraph(c) || std::isspace(c)) {
    value += c;
  } else {
    fail("Invalid Character in Value, got so far: ["s + value + "]"s);
  }
  return this;
}

auto ValueParserState::replaceSpecialCharacter(std::string &s) -> void {
  if (boost::algorithm::ends_with(s, R"(\"a)")) {
    boost::algorithm::replace_last(s, R"(\"a)", "ä");
  } else if (boost::algorithm::ends_with(s, R"(\"o)")) {
    boost::algorithm::replace_last(s, R"(\"o)", "ö");
  } else if (boost::algorithm::ends_with(s, R"(\"u)")) {
    boost::algorithm::replace_last(s, R"(\"u)", "ü");
  } else if (boost::algorithm::ends_with(s, R"(\ss)")) {
    boost::algorithm::replace_last(s, R"(\ss)", "ß");
  } else if (boost::algorithm::ends_with(s, R"(\'a)")) {
    boost::algorithm::replace_last(s, R"(\'a)", "á");
  } else if (boost::algorithm::ends_with(s, R"(\'e)")) {
    boost::algorithm::replace_last(s, R"(\'e)", "é");
  }
}
