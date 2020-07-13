#ifndef BIBPARSER_PARSER_HPP
#define BIBPARSER_PARSER_HPP

#include <TranslationTable.hpp>
#include <StyleProperties.hpp>
#include <BibElement.hpp>
#include <boost/filesystem.hpp>
#include <Field.hpp>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * Handles interaction with the bib-files and does parsing of it
 *
 * @brief interface to interact with bib-files
 */
class Parser {
private:
    class BibFileParser {
        struct ParserState {
            enum class InputState {
                GLOBAL, TYPENAME, IDENTIFIER, KEY, VALUE
            } inputState;
            BibElement result;
            std::size_t line;
            std::size_t col;
        };

    public:
        static auto setName(const std::string &name, ParserState &old) noexcept -> ParserState;

        static auto setStyle(const std::string &name, ParserState &old) noexcept -> ParserState;

        static auto setInputState(ParserState::InputState state, ParserState &old) noexcept -> ParserState;

        static auto setLastKey(const std::string &key, ParserState &old) noexcept -> ParserState;

        static auto setLastValue(const std::string &value, ParserState &old) noexcept -> ParserState;

        static auto elementsOf(std::string_view input) -> std::vector<BibElement>;
    };

    class ParserException : public std::runtime_error {
        std::size_t line;
        std::size_t column;
        std::string message;

    public:
        ParserException(size_t line, size_t column, std::string const &message);

    private:
        [[nodiscard]] const char *what() const noexcept override;
    };

    std::string targetStyle; ///< @property the target-style of the generated files
    TranslationTable translationTable; ///< @property translation-Table handler

    std::string convertUmlaut(std::string toConvert);

    std::string replaceUmlaut(std::string line);

    std::vector<BibElement> parseFile(boost::filesystem::ifstream &fsStream);

    void parseFiles(const boost::filesystem::path &path);

    Field parseField(std::string field, std::optional<StyleProperties> targetStructure, int &requiredFieldSize);

    BibElement parseElement(std::string style, std::string id, StyleProperties styleProps);

public:
    Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept;

    Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept;

    [[nodiscard]] auto generate(const boost::filesystem::path &inputPath,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;

    [[nodiscard]] auto generate(std::string_view inputFileContent,
                                const std::string &sorting) const noexcept -> std::vector<BibElement>;
};

#endif
