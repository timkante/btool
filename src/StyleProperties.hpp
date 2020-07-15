#ifndef BIBPARSER_STYLEPROPERTIES_HPP
#define BIBPARSER_STYLEPROPERTIES_HPP

#include <string>
#include <vector>

/**
 * Stores information of a styles properties
 * @brief style-properties-container
 */
struct StyleProperties {
  std::string name = ""; ///< name of the style
  std::vector<std::string> requiredFields = {}; ///< all the required fields
  std::vector<std::string> optionalFields = {}; ///< all the optional fields

  auto operator==(const StyleProperties &other) const noexcept -> bool;
};

#endif
