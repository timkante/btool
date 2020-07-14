#ifndef BIBPARSER_PARSERCONTEXT_HPP
#define BIBPARSER_PARSERCONTEXT_HPP

#include <cstddef>
#include <string>

struct ParserContext {
    std::string filename{};
    std::size_t line{1u};
    std::size_t column{0u};

    explicit ParserContext(std::string filename);
};

#endif
