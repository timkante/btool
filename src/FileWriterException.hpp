#ifndef BIBPARSER_SRC_FILEWRITEREXCEPTION_HPP_
#define BIBPARSER_SRC_FILEWRITEREXCEPTION_HPP_

#include <boost/filesystem/path.hpp>
#include <stdexcept>
#include <string>

/**
 * A File-Writing exception
 */
struct FileWriterException  : std::runtime_error {
  std::string message; ///< the message to throw

  FileWriterException(const boost::filesystem::path &file, const std::string &message);

  [[nodiscard]] auto what() const noexcept -> const char * override;
};

#endif
