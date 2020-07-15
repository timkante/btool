#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <unordered_set>

/**
 * Stores information of a styles properties
 * @brief style-properties-container
 */
struct StyleProperties {
  std::string name{}; ///< name of the style
  std::unordered_set<std::string> requiredFields{}; ///< all the required fields
  std::unordered_set<std::string> optionalFields{}; ///< all the optional fields

  auto operator==(const StyleProperties &other) const noexcept -> bool;
};

#endif
