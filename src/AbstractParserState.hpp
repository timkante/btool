#ifndef BIBPARSER_ABSTRACTPARSERSTATE_HPP
#define BIBPARSER_ABSTRACTPARSERSTATE_HPP

#include <vector>
#include <string>
#include <BibElement.hpp>
#include <ParserState.hpp>
#include <ParserContext.hpp>

class AbstractParserState : public ParserState {
protected:
    ParserContext &context;
    std::vector<BibElement> &result;

    [[noreturn]] auto fail(const std::string &message) -> void;

    auto handleCharacter(char c) -> ParserState * override;

public:
    AbstractParserState(ParserContext &context, std::vector<BibElement> &result) noexcept;
};

#endif
