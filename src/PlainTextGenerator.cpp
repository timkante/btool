#include <PlainTextGenerator.hpp>
#include <string>

/**
 * Writes all elements as plain text
 * @return the written output as String
 * @throws FileWriterException on error
 */
auto PlainTextGenerator::write() -> std::string {
  if (elements.empty()) fail("Cannot output empty results.", "");
  std::string result;
  for (const auto &element : elements){
    std::string repr = "@" + element.style + "{" + element.id + ",\n";
    for (const auto &key : sortedFields(element.attributes)){
      repr += "\t" + key.name + " = " + key.value + ",\n";
    }
    repr += "}\n";
    result += repr;
  }
  return result;
}

/**
 * Throws a HTML-Generator-Exception
 * @param message the message to append
 */
auto PlainTextGenerator::fail(const std::string &message, const std::string &type) -> void {
  AbstractGenerator::fail(message, "plain-text");
}

PlainTextGenerator::PlainTextGenerator(const std::vector<BibElement> &elements) : AbstractGenerator{elements} {};