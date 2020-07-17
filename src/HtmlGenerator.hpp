#ifndef BIBPARSER_SRC_HTMLGENERATOR_HPP_
#define BIBPARSER_SRC_HTMLGENERATOR_HPP_

#include <AbstractGenerator.hpp>
#include <unordered_map>
#include <ctml.hpp>

/**
 * HTML-Generator
 */
struct HtmlGenerator : public AbstractGenerator {

  /**
   * Enum that contains all known HTML tags.
   */
  enum class HtmlTag {
    TABLE,
    TABLE_BODY,
    TABLE_HEADING,
    TABLE_ENTRY,
    TABLE_ROW,
    LINK,
    SCRIPT,
    META,
    TITLE,
    H1,
    H5,
    DIV,
    BUTTON
  };

  [[noreturn]] auto fail(const std::string &message, const std::string &type = "HTML") -> void override;

  auto write() -> std::string override;

  static auto sortedKeys(const std::unordered_set<std::string> &set) noexcept -> std::vector<std::string>;

  auto fillContainer(CTML::Node &parent, const std::vector<std::string> keys) noexcept -> void;

  auto appendCard(
      CTML::Node &parent,
      const BibElement &element,
      const std::vector<std::string> keys
  ) noexcept -> void;

  auto appendTable(
      CTML::Node &parent,
      const BibElement &element,
      const std::vector<std::string> keys
  ) noexcept -> void;

  HtmlGenerator(const std::vector<BibElement> &elements);
};

template<HtmlGenerator::HtmlTag> inline const char *name = "Invalid HTML-Tag";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE> = "table";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_BODY> = "tbody";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_HEADING> = "th";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_ENTRY> = "td";
template<> inline const char *name<HtmlGenerator::HtmlTag::TABLE_ROW> = "tr";
template<> inline const char *name<HtmlGenerator::HtmlTag::LINK> = "link";
template<> inline const char *name<HtmlGenerator::HtmlTag::SCRIPT> = "script";
template<> inline const char *name<HtmlGenerator::HtmlTag::META> = "meta";
template<> inline const char *name<HtmlGenerator::HtmlTag::TITLE> = "title";
template<> inline const char *name<HtmlGenerator::HtmlTag::H1> = "h1";
template<> inline const char *name<HtmlGenerator::HtmlTag::H5> = "h5";
template<> inline const char *name<HtmlGenerator::HtmlTag::DIV> = "div";
template<> inline const char *name<HtmlGenerator::HtmlTag::BUTTON> = "button";

#endif
