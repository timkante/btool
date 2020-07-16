#include <HtmlGenerator.hpp>
#include <string>

/**
 * Throws a HTML-Generator-Exception
 * @param message the message to append
 */
auto HtmlGenerator::fail(const std::string &message, const std::string &type) -> void {
  AbstractGenerator::fail(message, type);
}

/**
 * Writes all elements as HTML-Document
 * @return the written document as String
 * @throws FileWriterException on error
 */
auto HtmlGenerator::write() -> std::string {
  if (elements.empty()){
    fail("Empty-Input is not Writable");
  }
  return AbstractGenerator::write();
}

/**
 * Constructor.
 * @param elements the elements to write.
 */
HtmlGenerator::HtmlGenerator(const std::vector<BibElement> &elements) : AbstractGenerator(elements) {}
