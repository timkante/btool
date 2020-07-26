#ifndef BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_
#define BIBPARSER_SRC_ABSTRACTGENERATOR_HPP_

#include <boost/filesystem/path.hpp>
#include <BibElement.hpp>
#include <Generator.hpp>
#include <Field.hpp>
#include <string>
#include <vector>

/**
 * Abstract Class with default-implementation of a File-Writer
 */
class AbstractGenerator : public Generator {
 protected:
  std::vector<BibElement> elements; ///< Elements to write

  [[noreturn]] virtual auto fail(const std::string &message, const std::string &type = "unknown") -> void;

  auto write() -> std::string override;

 public:
  explicit AbstractGenerator(std::vector<BibElement> elements);

  static auto uniqueFieldsOf(const std::vector<BibElement> &values) noexcept -> std::unordered_set<std::string>;

  static auto sortedFields(const std::vector<Field> &set) noexcept -> std::vector<Field>;
};

#endif
