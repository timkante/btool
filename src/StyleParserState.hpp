#ifndef BIBPARSER_STYLEPARSERSTATE_HPP
#define BIBPARSER_STYLEPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

/**
 * Style State of the Parser, parsing the style of the Bib-Element
 * @brief Style Parser State
 */
class StyleParserState : public AbstractParserState {
    std::string style; ///< a accumulator for style-characters while parsing it

public:

    StyleParserState(
            ParserContext &context,
            std::vector<BibElement> &result
    ) noexcept;

    auto handleCharacter(char c) -> ParserState * override;
};

#endif
