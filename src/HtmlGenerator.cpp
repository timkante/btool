#include <HtmlGenerator.hpp>
#include <sstream>
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
  if (elements.empty()) {
    fail("Empty-Input is not Writable");
  }
  auto keys = uniqueFieldsOf(elements);

  auto document = CTML::Document();
  auto table = CTML::Node(name<HtmlTag::TABLE>).SetAttribute("style", R"(width:100%)");

  auto tableHead = CTML::Node(name<HtmlTag::TABLE_ROW>);
  tableHead.AppendChild(CTML::Node(name<HtmlTag::TABLE_HEAD_ENTRY>, "identifier"));
  tableHead.AppendChild(CTML::Node(name<HtmlTag::TABLE_HEAD_ENTRY>, "style"));
  std::for_each(std::cbegin(keys), std::cend(keys), [&](const std::string &field) {
    tableHead.AppendChild(CTML::Node(name<HtmlTag::TABLE_HEAD_ENTRY>, field));
  });
  table.AppendChild(tableHead);

  std::for_each(std::cbegin(elements), std::cend(elements), [&](const BibElement &element) {
    auto row = CTML::Node(name<HtmlTag::TABLE_ROW>);
    row.AppendChild(CTML::Node(name<HtmlTag::TABLE_ENTRY>, element.id));
    row.AppendChild(CTML::Node(name<HtmlTag::TABLE_ENTRY>, element.style));
    std::for_each(std::cbegin(keys), std::cend(keys), [&](const std::string &field) {
      const auto val = element.findAttribute(field);
      row.AppendChild(
          CTML::Node(
              name<HtmlTag::TABLE_ENTRY>,
              val ? val.value().value : ""
          )
      );
    });
    table.AppendChild(row);
  });
  document.AppendNodeToBody(table);
  return document.ToString();
}

/**
 * Constructor.
 * @param elements the elements to write.
 */
HtmlGenerator::HtmlGenerator(const std::vector<BibElement> &elements) : AbstractGenerator{elements} {}
