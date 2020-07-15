#ifndef BIBPARSER_BIBELEMENT_HPP
#define BIBPARSER_BIBELEMENT_HPP

#include <StyleProperties.hpp>
#include <Field.hpp>
#include <optional>
#include <string>
#include <vector>

/**
 * Stores information of a bib-element
 * @brief bib-element-Container
 */
struct BibElement {
  std::string id; ///< the elements (unique) id
  std::string style; ///< the style-name of the element
  std::vector<Field> attributes; ///< the attributes of the element

  [[nodiscard]] auto isCompliantTo(const StyleProperties &props) const -> bool;

  auto operator==(const BibElement &other) const noexcept -> bool;

  [[nodiscard]] auto findAttribute(const std::string &key) const noexcept -> std::optional<Field>;
};

auto operator<<(std::ostream &os, BibElement const &elem) -> std::ostream &;

#endif
