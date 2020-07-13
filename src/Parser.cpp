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
    return BibFileParser::elementsOf(inContent);
}

auto Parser::generate(std::string_view inputFileContent,
                      const std::string &sorting) const noexcept -> std::vector<BibElement> {
    const std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    return BibFileParser::elementsOf(inputFileContent);
}

std::vector<BibElement> Parser::parseFile(boost::filesystem::ifstream &fsStream) {
    BibElement bibElem = parseElement("", "", StyleProperties());
    std::vector<BibElement> bibElems = {};
    std::string line;
    std::regex expr{"\\@(.*)\\{(.*)\\,"};
    std::smatch group;
    std::string fieldName;
    std::optional<StyleProperties> targetStructure = translationTable.stylePropertiesOf(targetStyle);
    int requiredFieldSize = targetStructure->requiredFields.size();
    bool styleMatch = false;
    while (std::getline(fsStream, line)) {
        boost::trim(line);
        if (std::regex_search(line, group, expr)) {
            styleMatch = group[1] == targetStyle;
            if (bibElem.id != "" && styleMatch) {
                if (requiredFieldSize > 0)
                    throw std::invalid_argument("Not all required Fields set in Element with ID: " + bibElem.id);
                bibElems.insert(bibElems.end(), bibElem);
            }
            if (styleMatch) {
                bibElem = parseElement(group[1], group[2], StyleProperties());
                requiredFieldSize = targetStructure->requiredFields.size();
            } else {
                continue;
            }

        } else if (styleMatch) {
            Field field = parseField(line, targetStructure, (int &) requiredFieldSize);
            if (field.name != "") {
                bibElem.attributes.insert(bibElem.attributes.end(), field);
            }
        }
    }
    if (requiredFieldSize > 0)
        throw std::invalid_argument("Not all required Fields set in Element with ID: " + bibElem.id);
    bibElems.insert(bibElems.end(), bibElem);
    return bibElems;
}

void Parser::parseFiles(const boost::filesystem::path &path) {
    boost::filesystem::directory_iterator it{path};
    bool bibFound = false;
    while (it != boost::filesystem::directory_iterator{}) {
        std::string fileExt = boost::filesystem::extension(*it);
        if (fileExt.compare(".bib") == 0) {
            bibFound = true;
            boost::filesystem::ifstream in(*it);
            parseFile(in);
        }
        *it++;
    }
    if (!bibFound) {
        std::cout << "Keine Bib Files im Pfad gefunden!\n";
        std::cout << path.string() << std::endl;
    }
}

Field Parser::parseField(std::string field, std::optional<StyleProperties> targetStructure, int &requiredFieldSize) {
    std::regex fieldExpr{"^\\s*(.*)\\s+=\\s+\\{*(.*?)\\}*\\,?$"};
    std::smatch group;
    if (std::regex_search(field, group, fieldExpr)) {

        std::string fieldName = group[1];
        boost::trim(fieldName);

        if (std::find(targetStructure->requiredFields.begin(), targetStructure->requiredFields.end(), fieldName) !=
            targetStructure->requiredFields.end()) {
            requiredFieldSize--;
            return Field(fieldName, replaceUmlaut(group[2]));
        }
        if (std::find(targetStructure->optionalFields.begin(), targetStructure->optionalFields.end(), fieldName) !=
            targetStructure->optionalFields.end()) {
            return Field(fieldName, replaceUmlaut(group[2]));
        }
    }
    return Field("", "");
}

BibElement Parser::parseElement(std::string style, std::string id, StyleProperties styleProps) {
    bool styleMatch = style == targetStyle;
    std::vector<Field> fields = {};
    if (styleMatch) {
        BibElement bibElem = BibElement(id, style, fields);
        return bibElem;
    } else {
        styleMatch = false;
    }
    return BibElement("", "", fields);
}

std::string Parser::replaceUmlaut(std::string line) {
    std::regex expr{"(\\{.*?\\})"};
    std::smatch group;
    std::string value = line;
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> tokenIterator(line.begin(), line.end(), expr);
    if (std::regex_search(value, group, expr)) {
        while (tokenIterator != rend) {
            std::string toConvert = (*tokenIterator).str();
            std::string umlaut = convertUmlaut(toConvert);
            std::size_t pos = value.find(toConvert);

            if (pos != std::string::npos) {
                value.replace(pos, toConvert.length(), umlaut);
            }

            *tokenIterator++;
        }
    }
    return value;
}

std::regex operator "" _re(char const *content, std::size_t len) {
    return std::regex{content};
}

std::string Parser::convertUmlaut(std::string toConvert) {
    if (toConvert == "{\\\"a}")
        return "ä";
    if (toConvert == "{\\\"o}")
        return "ö";
    if (toConvert == "{\\\"u}")
        return "ü";
    if (toConvert == "{\\ss}")
        return "ß";
    if (toConvert == "{\\\'a}")
        return "á";
    if (toConvert == "{\\\'e}")
        return "é";

    throw std::invalid_argument("no valid Umlaut: " + toConvert);
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