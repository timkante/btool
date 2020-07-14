#ifndef BIBPARSER_VALUEPARSERSTATE_HPP
#define BIBPARSER_VALUEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <cctype>
#include <vector>
#include <string>
#include <stack>

class ValueParserState : public AbstractParserState {
    std::string value;
    std::stack<std::pair<std::size_t, std::size_t>> braces;

public:
    ValueParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
