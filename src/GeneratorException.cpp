#include <GeneratorException.hpp>
#include <utility>

/**
 * Exception-Message
 * @return the exception-message
 */
auto GeneratorException::what() const noexcept -> const char * {
  return message.c_str();
}

/**
 * Constructor.
 * @param file the file to error on
 * @param message the message to throw
 */
GeneratorException::GeneratorException(
    std::string message
) : std::runtime_error{""},
    message{std::move(message)} {}
