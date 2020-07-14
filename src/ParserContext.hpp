#ifndef BIBPARSER_PARSERCONTEXT_HPP
#define BIBPARSER_PARSERCONTEXT_HPP

#include <cstddef>
#include <string>

/**
 * Context of a Parser-State
 */
struct ParserContext {
    std::string filename{}; ///< @property the filename of the currently parsed-file
    std::size_t line{1U}; ///< @property the current line the parser is parsing
    std::size_t column{0U}; ///< @property the current column the parser is parsing

    /**
     * Constructor.
     * @param filename the filename of the file to parse
     */
    explicit ParserContext(std::string filename);
};

#endif
