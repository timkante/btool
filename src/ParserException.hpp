#ifndef BIBPARSER_PARSEREXCEPTION_HPP
#define BIBPARSER_PARSEREXCEPTION_HPP

#include <ParserContext.hpp>
#include <AbstractParserState.hpp>
#include <stdexcept>
#include <string>

struct ParserException : public std::runtime_error {
    ParserState * state;
    const ParserContext context;
    const std::string message;

    ParserException(AbstractParserState *state, const ParserContext &context, const std::string &message);

    [[nodiscard]] auto what() const noexcept -> const char * override;
};

#endif
