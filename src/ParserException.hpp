#ifndef BIBPARSER_PARSEREXCEPTION_HPP
#define BIBPARSER_PARSEREXCEPTION_HPP

#include <ParserContext.hpp>
#include <AbstractParserState.hpp>
#include <stdexcept>
#include <string>

/**
 * A Parsing-Exception
 */
struct ParserException : std::runtime_error {
    ParserState * state; ///< @property the state of the parser
    const ParserContext context; ///< @property the context of the parser
    const std::string message; ///< @property the message to throw

    /**
     * Constructor.
     * @param state the state of the parser
     * @param context the context of the parser
     * @param message the message to throw
     */
    ParserException(AbstractParserState *state, const ParserContext &context, const std::string &message);

    /**
     * Exception-Message
     * @return the exception-message
     */
    [[nodiscard]] auto what() const noexcept -> const char * override;
};

#endif
