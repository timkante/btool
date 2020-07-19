#include <HtmlGenerator.hpp>
#include <string>

/**
 * Throws a HTML-Generator-Exception
 * @param message the message to append
 */
auto HtmlGenerator::fail(const std::string &message, const std::string &type) -> void {
  AbstractGenerator::fail(message, "HTML");
}

/**
 * Writes all elements as HTML-Document (wrapped by Bootstrap)
 * @return the written document as String
 * @throws FileWriterException on error
 */
auto HtmlGenerator::write() -> std::string {
  if (elements.empty()) {
    fail("Empty-Input is not Writable");
  }
  auto keys = uniqueFieldsOf(elements);

  auto document = CTML::Document();
  document.head()
      .AppendChild(
          CTML::Node(name<HtmlTag::META>)
              .SetAttribute("charset", "utf-8")
              .UseClosingTag(false)
      )
      .AppendChild(
          CTML::Node(name<HtmlTag::META>)
              .SetAttribute("name", "viewport")
              .SetAttribute("content", "width=device-width, initial-scale=1, shrink-to-fit=no")
              .UseClosingTag(false)
      )
      .AppendChild(
          CTML::Node(name<HtmlTag::LINK>)
              .SetAttribute("rel", "stylesheet")
              .SetAttribute("href", "https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css")
              .SetAttribute("integrity", "sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm")
              .SetAttribute("crossorigin", "anonymous")
              .UseClosingTag(false)
      )
      .AppendChild(
          CTML::Node(name<HtmlTag::TITLE>, "Bib-Parser results")
      );

  auto container = CTML::Node(name<HtmlTag::DIV>).ToggleClass("container");

  fillContainer(container, sortedKeys(keys));

  document.body()
      .AppendChild(container)
      .AppendChild(
          CTML::Node(name<HtmlTag::SCRIPT>)
              .SetAttribute("src", "https://code.jquery.com/jquery-3.2.1.slim.min.js")
              .SetAttribute("integrity", "sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN")
              .SetAttribute("crossorigin", "anonymous")
      )
      .AppendChild(
          CTML::Node(name<HtmlTag::SCRIPT>)
              .SetAttribute("src", "https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js")
              .SetAttribute("integrity", "sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q")
              .SetAttribute("crossorigin", "anonymous")
      )
      .AppendChild(
          CTML::Node(name<HtmlTag::SCRIPT>)
              .SetAttribute("src", "https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js")
              .SetAttribute("integrity", "sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl")
              .SetAttribute("crossorigin", "anonymous")
      );
  return document.ToString();
}

/**
 * Constructor.
 * @param elements the elements to write.
 */
HtmlGenerator::HtmlGenerator(const std::vector<BibElement> &elements) : AbstractGenerator{elements} {}

/**
 * Fills the Main Container-Div of the Page-Body
 * @param parent[out] The Parent node (Container-Div)
 * @param keys all the Field-Keys to handle (sorted)
 */
void HtmlGenerator::fillContainer(
    CTML::Node &parent,
    const std::vector<std::string> &keys
) noexcept {
  auto accordion = CTML::Node(name<HtmlTag::DIV>).SetAttribute("id", "accordion");
  for (const auto &element: elements) {
    appendCard(accordion, element, keys);
  }
  parent.AppendChild(accordion);
}

/**
 * Creates A Card for an element and appends it to the Parent
 * @param parent[out] the node the Card gets appended to
 * @param element the element to create the Card for
 * @param keys all possible Field-Keys (sorted)
 */
auto HtmlGenerator::appendCard(
    CTML::Node &parent,
    const BibElement &element,
    const std::vector<std::string> &keys
) noexcept -> void {
  auto card = CTML::Node(name<HtmlTag::DIV>).ToggleClass("card");

  auto cardHeader = CTML::Node(name<HtmlTag::DIV>)
      .ToggleClass("card-header")
      .SetAttribute("id", element.id);

  auto headerHeading = CTML::Node(name<HtmlTag::H5>).ToggleClass("mb-0");

  auto button = CTML::Node(
      name<HtmlTag::BUTTON>,
      element.id + " - " + element.findAttribute("title").value_or<Field>({"", ""}).value
  )
      .ToggleClass("btn btn-link collapsed")
      .SetAttribute("data-toggle", "collapse")
      .SetAttribute("data-target", "#collapse" + element.id)
      .SetAttribute("aria-expanded", "false")
      .SetAttribute("aria-controls", "collapse" + element.id);

  auto cardBodyWrapper = CTML::Node(name<HtmlTag::DIV>)
      .ToggleClass("collapse")
      .SetAttribute("id", "collapse" + element.id)
      .SetAttribute("aria-labelledby", element.id)
      .SetAttribute("data-parent", "#accordion");

  auto cardBody = CTML::Node(name<HtmlTag::DIV>).ToggleClass("card-body");

  appendTable(cardBody, element, keys);

  cardBodyWrapper.AppendChild(cardBody);
  headerHeading.AppendChild(button);
  cardHeader.AppendChild(headerHeading);
  card.AppendChild(cardHeader);
  card.AppendChild(cardBodyWrapper);
  parent.AppendChild(card);
}

/**
 * Appends a table of all Element-Atrributes to a node
 * @param parent[out] the node to append the table to
 * @param element the element to create the table for
 * @param keys all possible Field-Keys (sorted)
 */
auto HtmlGenerator::appendTable(
    CTML::Node &parent,
    const BibElement &element,
    const std::vector<std::string> &keys
) noexcept -> void {
  auto table = CTML::Node(name<HtmlTag::TABLE>).ToggleClass("table");
  auto tableBody = CTML::Node(name<HtmlTag::TABLE_BODY>);
  for (const auto &key : keys) {
    auto row = CTML::Node(name<HtmlTag::TABLE_ROW>)
        .AppendChild(CTML::Node(name<HtmlTag::TABLE_HEADING>, key).SetAttribute("scope", "row"))
        .AppendChild(CTML::Node(
            name<HtmlTag::TABLE_ENTRY>,
            element.findAttribute(key).value_or<Field>({"", ""}).value
        ));
    tableBody.AppendChild(row);
  }

  table.AppendChild(tableBody);
  parent.AppendChild(table);
}
