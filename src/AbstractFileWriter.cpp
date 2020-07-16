#include <AbstractFileWriter.hpp>
#include <FileWriterException.hpp>

/**
 * Helper Method to construct sufficient error-messages
 * @param message the message to use
 * @throws FileWriterException (always)
 */
auto AbstractFileWriter::fail(const std::string &message) -> void {
  throw FileWriterException{filepath, message};
}

/**
 * Constructor.
 * @param elements the elements to write into the file
 * @param filepath the target-path of the output-file
 */
AbstractFileWriter::AbstractFileWriter(
    const std::vector<BibElement> &elements,
    const boost::filesystem::path &filepath
) : elements{elements}, filepath{filepath} {}
