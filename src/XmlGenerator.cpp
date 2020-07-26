#include <XmlGenerator.hpp>
#include <sstream>

/**
 * Constructor.
 * @param elements the elements to write.
 */
XmlGenerator::XmlGenerator(const std::vector<BibElement> &elements) : AbstractGenerator{elements} {}

/**
 * Writes all elements in XML-Format
 * @return the written output as String
 * @throws FileWriterException on error
 */
auto XmlGenerator::write() -> std::string {
  std::stringstream ss;
  ss << R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)" << '\n';
  ss << "<bibElements>\n";
  for (const auto & element : elements) {
    ss << "\t<element>\n";
    ss << "\t\t<id>\n\t\t\t" << element.id << "\n\t\t</id>\n";
    ss << "\t\t<style>\n\t\t\t" << element.style << "\n\t\t</style>\n";
    ss << "\t\t<attributes>\n";
    for (const auto & attribute : element.attributes) {
      ss << "\t\t\t<" << attribute.name << ">" << attribute.value << "</" << attribute.name << ">\n";
    }
    ss << "\t\t</attributes>\n";
    ss << "\t</element>\n";
  }
  ss << "</bibElements>\n";
  return ss.str();
}

/**
 * Throws a XML-Generator-Exception
 * @param message the message to append
 */
auto XmlGenerator::fail(const std::string &message, const std::string &type) -> void {
  AbstractGenerator::fail(message, "XML");
}
