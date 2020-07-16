#ifndef BIBPARSER_SRC_ABSTRACTFILEWRITER_HPP_
#define BIBPARSER_SRC_ABSTRACTFILEWRITER_HPP_

#include <boost/filesystem/path.hpp>
#include <BibElement.hpp>
#include <FileWriter.hpp>
#include <string>
#include <vector>

/**
 * Abstract Class with default-implementation of a File-Writer
 */
class AbstractFileWriter : public FileWriter {
 protected:
  std::vector<BibElement> elements; ///< Elements to write
  boost::filesystem::path filepath; ///< Path to write the file to

  [[noreturn]] auto fail(const std::string &message) -> void;

 public:

  AbstractFileWriter(const std::vector<BibElement> &elements, const boost::filesystem::path &filepath);
};

#endif
