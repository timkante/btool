#ifndef BIBPARSER_VALUEPARSERSTATE_HPP
#define BIBPARSER_VALUEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <cctype>
#include <vector>
#include <string>
#include <stack>

/**
 * Value State of the Parser, parsing the value of the last Bib-Elements properties key
 * @brief Key Parser State
 */
class ValueParserState : public AbstractParserState {
    std::string value; ///< a accumulator for value-characters while parsing it
    std::stack<std::pair<std::size_t, std::size_t>> braces; ///< a stack for counting delimiting braces

public:

    ValueParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
