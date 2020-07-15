#ifndef BIBPARSER_PARSERCONTEXT_HPP
#define BIBPARSER_PARSERCONTEXT_HPP

#include <cstddef>
#include <string>

/**
 * Context of a Parser-State
 */
struct ParserContext {
  std::string filename{}; ///< the filename of the currently parsed-file
  std::size_t line{1U}; ///< the current line the parser is parsing
  std::size_t column{0U}; ///< the current column the parser is parsing

  explicit ParserContext(std::string filename);
};

#endif
