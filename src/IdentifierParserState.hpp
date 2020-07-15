#ifndef BIBPARSER_IDENTIFIERPARSERSTATE_HPP
#define BIBPARSER_IDENTIFIERPARSERSTATE_HPP

#include <AbstractParserState.hpp>
#include <ParserContext.hpp>
#include <BibElement.hpp>
#include <vector>
#include <string>

/**
 * Identifier State of the Parser, parsing the identifier of the Bib-Element
 * @brief Identifier Parser State
 */
class IdentifierParserState : public AbstractParserState {
  std::string identifier; ///< a accumulator for identifier-characters while parsing it

 public:

  IdentifierParserState(
      ParserContext &context,
      std::vector<BibElement> &result
  ) noexcept;

  auto handleCharacter(char c) -> ParserState * override;
};

#endif
