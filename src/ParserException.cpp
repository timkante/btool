#include "ParserException.hpp"
#include <string>

ParserException::ParserException(AbstractParserState *state, const ParserContext &context, const std::string &message)
        : std::runtime_error{""},
          state{state},
          context{context},
          message{
                  context.filename + ":" + std::to_string(context.line)
                  + ":" + std::to_string(context.column) + " - " + message
          } {}

auto ParserException::what() const noexcept -> const char * {
    return message.c_str();
}
