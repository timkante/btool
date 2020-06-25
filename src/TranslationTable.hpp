#ifndef BIBPARSER_TRANSLATIONTABLE_HPP
#define BIBPARSER_TRANSLATIONTABLE_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include <StyleProperties.hpp>
#include <optional>
#include <iostream>
#include <sstream>
#include <vector>

class TranslationTable {
private:
    boost::property_tree::ptree contents;
    std::vector<StyleProperties> styleProperties;

    [[nodiscard]] static auto parseStyle(const boost::property_tree::ptree &style) -> StyleProperties;

    [[nodiscard]] auto parseStyles() const -> std::vector<StyleProperties>;

public:
    explicit TranslationTable(std::stringstream file);

    explicit TranslationTable(const boost::filesystem::path &path);

    auto printAll(std::ostream &out = std::cout) const -> void;

    [[nodiscard]] auto getStyleProperties() const -> const std::vector<StyleProperties> &;

    [[nodiscard]] auto stylePropertiesOf(const std::string &name) const -> std::optional<StyleProperties>;
};

#endif
