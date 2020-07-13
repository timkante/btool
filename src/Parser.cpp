#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <Parser.hpp>
#include <sstream>
#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>

Parser::Parser(const boost::filesystem::path &ruleFilePath, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(ruleFilePath)) {}

Parser::Parser(std::stringstream ruleFileContents, std::string targetStyle) noexcept
        : targetStyle(std::move(targetStyle)), translationTable(TranslationTable(std::move(ruleFileContents))) {}

auto Parser::generate(const boost::filesystem::path &inputPath,
                      const std::string &sorting) const noexcept -> std::vector<BibElement> {
    std::ifstream inFile{inputPath.string()};
    std::string inContent{std::istream_iterator<char>{inFile}, std::istream_iterator<char>{}};
    return generate(std::string_view(inContent), sorting);
}

auto Parser::generate(std::string_view inputFileContent,
                      const std::string &sorting) const noexcept -> std::vector<BibElement> {
    const std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    return BibFileParser::elementsOf(inputFileContent);
}

auto Parser::BibFileParser::elementsOf(std::string_view input) -> std::vector<BibElement> {
    std::size_t braceCount = 0;
    std::vector<BibElement> result{};
    auto currentState = ParserState{
            ParserState::InputState::GLOBAL,
            {"", "", {}},
            1,
            0
    };
    for (char const ch : input) {
        ++currentState.col;
        if (ch == '\n') {
            ++currentState.line;
            currentState.col = 0;
            continue;
        }

        switch (currentState.inputState) {
            case ParserState::InputState::GLOBAL:
                currentState.inputState =
                        ch == '@' ? ParserState::InputState::TYPENAME : ParserState::InputState::GLOBAL;
                break;
            case ParserState::InputState::TYPENAME:
                if (ch == '{') {
                    if (currentState.result.style.empty())
                        throw ParserException(currentState.line, currentState.col, "Style-Name must not be empty.");
                    else
                        currentState = setInputState(ParserState::InputState::IDENTIFIER, currentState);
                } else if (std::isgraph(ch)) {
                    currentState = setStyle(currentState.result.style + ch, currentState);
                } else {
                    throw ParserException(currentState.line, currentState.col, "Invalid Character in Style-Name.");
                }
                break;
            case ParserState::InputState::IDENTIFIER:
                if (ch == ',') {
                    if (currentState.result.id.empty())
                        throw ParserException(currentState.line, currentState.col, "Identifier must not be empty.");
                    else {
                        setInputState(ParserState::InputState::KEY, currentState);
                        setLastKey("", currentState);
                    }
                } else if (std::isgraph(ch)) {
                    currentState = setName(currentState.result.id + ch, currentState);
                } else {
                    throw ParserException(currentState.line, currentState.col, "Invalid Character in Identifier.");
                }
                break;
            case ParserState::InputState::KEY:
                if (std::isspace(ch)) {
                    continue;
                } else if (ch == '=') {
                    if (currentState.result.attributes.back().name.empty())
                        throw ParserException(currentState.line, currentState.col, "Key must not be empty.");
                    else
                        currentState = setInputState(ParserState::InputState::VALUE, currentState);
                } else if (std::isgraph(ch)) {
                    currentState = setLastKey(currentState.result.attributes.back().name + ch, currentState);
                } else {
                    throw ParserException(currentState.line, currentState.col, "Invalid Character in Key.");
                }
                break;
            case ParserState::InputState::VALUE:
                if (std::isspace(ch)) {
                    setLastValue(currentState.result.attributes.back().value + ch, currentState);
                } else if (ch == ',') {
                    if (currentState.result.attributes.back().value.empty())
                        throw ParserException(currentState.line, currentState.col, "Value must not be empty.");
                    else if (braceCount != 0)
                        throw ParserException(currentState.line, currentState.col, "Unexpected end of value.");
                    else {
                        setInputState(ParserState::InputState::KEY, currentState);
                        setLastKey("", currentState);
                    }
                } else if (ch == '{') {
                    ++braceCount;
                    setLastValue(currentState.result.attributes.back().value + ch, currentState);
                } else if (ch == '}') {
                    if (braceCount == 0) {
                        result.push_back(currentState.result);
                        currentState.result = {"", "", {}};
                        currentState = setInputState(ParserState::InputState::GLOBAL, currentState);
                    } else {
                        setLastValue(currentState.result.attributes.back().value + ch, currentState);
                        --braceCount;
                    }
                } else if (std::isgraph(ch)) {
                    currentState = setLastValue(currentState.result.attributes.back().value + ch, currentState);
                } else {
                    throw ParserException(currentState.line, currentState.col, "Invalid Character in Value.");
                }
                break;
        }
    }
    if (currentState.inputState != ParserState::InputState::GLOBAL)
        throw ParserException(currentState.line, currentState.col, "Unexpected End of File.");
    return result;
}

std::string formatException(
        size_t line,
        size_t column,
        const std::string &message
) {
    std::ostringstream formatter{};
    formatter << line << ":" << column << " - " << message;
    return formatter.str();
}

Parser::ParserException::ParserException(
        size_t line,
        size_t column,
        std::string const &message
) : std::runtime_error(""), line(line), column(column), message(formatException(line, column, message)) {}

const char *Parser::ParserException::what() const noexcept {
    return message.c_str();
}

auto Parser::BibFileParser::setName(
        const std::string &name,
        ParserState &old
) noexcept -> ParserState {
    old.result.id = name;
    return old;
}

auto Parser::BibFileParser::setStyle(
        const std::string &name,
        ParserState &old
) noexcept -> ParserState {
    old.result.style = name;
    return old;
}

auto Parser::BibFileParser::setInputState(
        ParserState::InputState state,
        ParserState &old
) noexcept -> ParserState {
    old.inputState = state;
    return old;
}

auto Parser::BibFileParser::setLastKey(
        const std::string &key,
        ParserState &old
) noexcept -> ParserState {
    if (key.empty()) old.result.attributes.emplace_back("", "");
    else old.result.attributes.back().name = key;
    return old;
}

auto Parser::BibFileParser::setLastValue(
        const std::string &value,
        ParserState &old
) noexcept -> ParserState {
    old.result.attributes.back().value = value;
    return old;
}