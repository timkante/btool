#include <ParserContext.hpp>
#include <utility>

/**
 * Constructor.
 * @param filename the filename of the file to parse
 */
ParserContext::ParserContext(std::string filename) : filename{std::move(filename)} {}
