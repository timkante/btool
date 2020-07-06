#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include <StyleProperties.hpp>
#include <optional>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Handles interaction with the translation-table-file and does parsing of it
 *
 * @brief interface to interact with translation-table resource
 */
class TranslationTable {
private:
    boost::property_tree::ptree contents; ///< @property pointer to parsed json-tree
    std::vector<StyleProperties> styleProperties; ///< @property parsed style-properties

    [[nodiscard]] static auto parseStyle(const boost::property_tree::ptree &style) -> StyleProperties;

    /**
     * Parses Styles of a top-level json-pointer (tree according to proposed structure)
     *
     * @return all the parsed style properties
     */
    [[nodiscard]] auto parseStyles() const -> std::vector<StyleProperties>;

public:
    /**
     * Constructor.
     *
     * @param file contents of a file
     */
    explicit TranslationTable(std::stringstream file);

    /**
     * Constructor.
     *
     * @param path path to a translation-table json-file
     */
    explicit TranslationTable(const boost::filesystem::path &path);

    /**
     * Prints the content of contents
     *
     * @param out the ostream to print into
     */
    auto printAll(std::ostream &out = std::cout) const -> void;

    /**
     * Provides all parsed style-properties
     *
     * @return all parsed style-properties
     */
    [[nodiscard]] auto getStyleProperties() const -> const std::vector<StyleProperties> &;

    /**
     * Provides style-properties for a specific style
     *
     * @param name the style name to get properties for
     * @return (maybe) the properties for the style - None if there are none
     */
    [[nodiscard]] auto stylePropertiesOf(const std::string &name) const -> std::optional<StyleProperties>;
};

#endif
