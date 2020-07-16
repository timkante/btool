#ifndef BIBPARSER_SRC_HTMLGENERATOR_HPP_
#define BIBPARSER_SRC_HTMLGENERATOR_HPP_

#include <AbstractGenerator.hpp>

/**
 * HTML-Generator
 */
struct HtmlGenerator : public AbstractGenerator {
  [[noreturn]] auto fail(const std::string &message, const std::string &type = "HTML") -> void override;

  auto write() -> std::string override;

  HtmlGenerator(const std::vector<BibElement> &elements);
};

#endif
