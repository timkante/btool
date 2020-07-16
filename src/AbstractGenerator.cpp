#include <AbstractGenerator.hpp>
#include <GeneratorException.hpp>

/**
 * Helper Method to construct sufficient error-messages
 * @param message the message to use
 * @throws FileWriterException (always)
 */
auto AbstractGenerator::fail(const std::string &message, const std::string &type) -> void {
  throw GeneratorException{"[" + type + " generator]: ", message};
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
