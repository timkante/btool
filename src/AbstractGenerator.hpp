#ifndef BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_
#define BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_

#include <boost/filesystem/path.hpp>
#include <BibElement.hpp>
#include <Generator.hpp>
#include <string>
#include <vector>

/**
 * Abstract Class with default-implementation of a File-Writer
 */
class AbstractGenerator : public Generator {
 protected:
  const std::vector<BibElement> &elements; ///< Elements to write

  [[noreturn]] virtual auto fail(const std::string &message, const std::string &type = "unknown") -> void;

  auto write() const -> std::string;

 public:

  AbstractGenerator(const std::vector<BibElement> &elements);
};

#endif
