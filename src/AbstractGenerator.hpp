#ifndef BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_
#define BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_

#include <boost/filesystem/path.hpp>
#include <BibElement.hpp>
#include <Generator.hpp>
#include <unordered_set>
#include <string>
#include <vector>

/**
 * Abstract Class with default-implementation of a File-Writer
 */
class AbstractGenerator : public Generator {
 protected:
  std::vector<BibElement> elements; ///< Elements to write

  [[noreturn]] virtual auto fail(const std::string &message, const std::string &type = "unknown") -> void;

  auto write() -> std::string;

 public:

  AbstractGenerator(std::vector<BibElement> elements);

  static auto uniqueFieldsOf(const std::vector<BibElement> &values) noexcept -> std::unordered_set<std::string>;

  static auto sortedKeys(const std::unordered_set<std::string> &set) noexcept -> std::vector<std::string>;
};

#endif
