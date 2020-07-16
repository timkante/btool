#include <FileWriterException.hpp>

/**
 * Exception-Message
 * @return the exception-message
 */
auto FileWriterException::what() const noexcept -> const char * {
  return message.c_str();
}

/**
 * Constructor.
 * @param file the file to error on
 * @param message the message to throw
 */
FileWriterException::FileWriterException(
    const boost::filesystem::path &file,
    const std::string &message
) : std::runtime_error{""},
    message{file.string() + ": " + message} {}
