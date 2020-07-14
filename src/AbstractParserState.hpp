#ifndef BIBPARSER_ABSTRACTPARSERSTATE_HPP
#define BIBPARSER_ABSTRACTPARSERSTATE_HPP

#include <vector>
#include <string>
#include <BibElement.hpp>
#include <ParserState.hpp>
#include <ParserContext.hpp>

/**
 * Abstract Class with default-implementation of a ParserState
 */
class AbstractParserState : public ParserState {
protected:
    ParserContext &context; ///< Context of the State
    std::vector<BibElement> &result; ///< Container for accumulating Parsing-Results

    [[noreturn]] auto fail(const std::string &message) -> void;

    auto handleCharacter(char c) -> ParserState * override;

public:

    AbstractParserState(ParserContext &context, std::vector<BibElement> &result) noexcept;
};

#endif
