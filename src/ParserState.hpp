#ifndef BIBPARSER_PARSERSTATE_HPP
#define BIBPARSER_PARSERSTATE_HPP

struct ParserState {
    virtual ~ParserState() = default;

    virtual auto handleCharacter(char c) -> ParserState * = 0;
};

#endif
