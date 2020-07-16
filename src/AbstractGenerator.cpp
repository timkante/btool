#include <AbstractGenerator.hpp>
#include <FileWriterException.hpp>

/**
 * Helper Method to construct sufficient error-messages
 * @param message the message to use
 * @throws FileWriterException (always)
 */
auto AbstractGenerator::fail(const std::string &message) -> void {
  throw FileWriterException{"[unknown generator]: ", message};
}

/**
 * Constructor.
 * @param elements the elements to write
 */
AbstractGenerator::AbstractGenerator(const std::vector<BibElement> &elements) : elements{elements} {}

/**
 * Default write-behaviour (do nothing)
 * @return the elements in target format
 */
auto AbstractGenerator::write() const -> std::string {
  return "";
}
