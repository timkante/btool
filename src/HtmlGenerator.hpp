#ifndef BIBPARSER_SRC_HTMLGENERATOR_HPP_
#define BIBPARSER_SRC_HTMLGENERATOR_HPP_

#include <AbstractGenerator.hpp>
#include <unordered_map>
#include <ctml.hpp>

/**
 * HTML-Generator
 */
struct HtmlGenerator : public AbstractGenerator {

  enum class HtmlTag {
    TABLE,
    TABLE_ROW,
    TABLE_ENTRY,
    TABLE_HEAD_ENTRY
  };

  [[noreturn]] auto fail(const std::string &message, const std::string &type = "HTML") -> void override;

  auto write() -> std::string override;

  HtmlGenerator(const std::vector<BibElement> &elements);
};

template<HtmlGenerator::HtmlTag> inline const char *name = "Invalid HTML-Tag";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE> = "table";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_ROW> = "tr";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_ENTRY> = "td";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_HEAD_ENTRY> = "th";

#endif
