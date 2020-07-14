#include <ParserException.hpp>
#include <string>

/**
 * Constructor.
 * @param state the state of the parser
 * @param context the context of the parser
 * @param message the message to throw
 */
ParserException::ParserException(AbstractParserState *state, const ParserContext &context, const std::string &message)
        : std::runtime_error{""},
          state{state},
          context{context},
          message{
                  context.filename + ":" + std::to_string(context.line)
                  + ":" + std::to_string(context.column) + " - " + message
          } {}

/**
 * Exception-Message
 * @return the exception-message
 */
auto ParserException::what() const noexcept -> const char * {
    return message.c_str();
}
