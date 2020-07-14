#include "ParserContext.hpp"

#include <utility>

ParserContext::ParserContext(std::string filename) : filename{std::move(filename)}, line{1u}, column{0u} {}