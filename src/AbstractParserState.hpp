#ifndef BIBPARSER_ABSTRACTPARSERSTATE_HPP
#define BIBPARSER_ABSTRACTPARSERSTATE_HPP

#include <vector>
#include <string>
#include <BibElement.hpp>
#include <ParserState.hpp>
#include <ParserContext.hpp>

/**
 * Abstract Class with default-implementation of a ParserState
 * @implements ParserState
 */
class AbstractParserState : public ParserState {
protected:
    ParserContext &context; ///< @property Context of the State
    std::vector<BibElement> &result; ///< @property Container for accumulating Parsing-Results

    /**
     * Error handling on parsing-error
     * @param message Error-Message to display
     * @throws ParserException (always)
     */
    [[noreturn]] auto fail(const std::string &message) -> void;

    /**
     * Behaviour of a State to parse next Character
     * @param c the next character
     * @return a new Parser-State
     */
    auto handleCharacter(char c) -> ParserState * override;

public:

    /**
     * Constructor.
     * @param context the context of the State
     * @param result an accumulator for results
     */
    AbstractParserState(ParserContext &context, std::vector<BibElement> &result) noexcept;
};

#endif
