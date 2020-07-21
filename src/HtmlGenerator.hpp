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

  auto fillContainer(
      CTML::Node &parent,
      const std::vector<std::string> &keys
  ) noexcept -> void;

  auto appendCard(
      CTML::Node &parent,
      const BibElement &element,
      const std::vector<std::string> &keys
  ) noexcept -> void;

  auto appendTable(
      CTML::Node &parent,
      const BibElement &element,
      const std::vector<std::string> &keys
  ) noexcept -> void;

  explicit HtmlGenerator(const std::vector<BibElement> &elements);
};

template<HtmlGenerator::HtmlTag> inline char const * const name = "Invalid HTML-Tag";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TABLE> = "table";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TABLE_BODY> = "tbody";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TABLE_HEADING> = "th";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TABLE_ENTRY> = "td";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TABLE_ROW> = "tr";
template<> inline char const * const name<HtmlGenerator::HtmlTag::LINK> = "link";
template<> inline char const * const name<HtmlGenerator::HtmlTag::SCRIPT> = "script";
template<> inline char const * const name<HtmlGenerator::HtmlTag::META> = "meta";
template<> inline char const * const name<HtmlGenerator::HtmlTag::TITLE> = "title";
template<> inline char const * const name<HtmlGenerator::HtmlTag::H1> = "h1";
template<> inline char const * const name<HtmlGenerator::HtmlTag::H5> = "h5";
template<> inline char const * const name<HtmlGenerator::HtmlTag::DIV> = "div";
template<> inline char const * const name<HtmlGenerator::HtmlTag::BUTTON> = "button";

#endif
