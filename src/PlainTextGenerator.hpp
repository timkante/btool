#ifndef BTOOL_SRC_PLAINTEXTGENERATOR_HPP_
#define BTOOL_SRC_PLAINTEXTGENERATOR_HPP_

#include <AbstractGenerator.hpp>

struct PlainTextGenerator : AbstractGenerator {

  [[noreturn]] auto fail(const std::string &message, const std::string &type) -> void override;

  auto write() -> std::string override;

  explicit PlainTextGenerator(const std::vector<BibElement> &elements);
};

#endif
