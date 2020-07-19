#include <AbstractGenerator.hpp>
#include <GeneratorException.hpp>
#include <Field.hpp>
#include <unordered_set>
#include <utility>

/**
 * Helper Method to construct sufficient error-messages
 * @param message the message to use
 * @throws FileWriterException (always)
 */
auto AbstractGenerator::fail(
    const std::string &message,
    const std::string &type
) -> void {
  throw GeneratorException{"[" + type + " generator]: " + message};
}

/**
 * Constructor.
 * @param elements the elements to write
 */
AbstractGenerator::AbstractGenerator(std::vector<BibElement> elements) : elements{std::move(elements)} {}

/**
 * Default write-behaviour (do nothing)
 * @return the elements in target format
 */
auto AbstractGenerator::write() -> std::string {
  return "";
}

auto AbstractGenerator::uniqueFieldsOf(
    const std::vector<BibElement> &values
) noexcept -> std::unordered_set<std::string> {
  std::unordered_set<std::string> result{};
  std::for_each(std::cbegin(values),
                std::cend(values),
                [&](const BibElement &element) {
                  std::transform(std::cbegin(element.attributes),
                                 std::cend(element.attributes),
                                 std::inserter(result, std::end(result)),
                                 [](const Field &field) {
                                   return field.name;
                                 });
                });
  return result;
}

/**
 * Sorts a unordered Set of keys into a vector
 * @param set the unordered set of keys
 * @return the sorted vector of keys
 */
auto AbstractGenerator::sortedKeys(
    const std::unordered_set<std::string> &set
) noexcept -> std::vector<std::string> {
  std::vector<std::string> sortedKeys{std::cbegin(set), std::cend(set)};
  std::sort(std::begin(sortedKeys), std::end(sortedKeys));
  return sortedKeys;
}
