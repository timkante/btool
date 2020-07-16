#ifndef BIBPARSER_PARSERSTATE_HPP
#define BIBPARSER_PARSERSTATE_HPP

/**
 * A parser state interface
 */
struct ParserState {

  /**
   * default destructor.
   */
  virtual ~ParserState() = default;

  /**
   * Behaviour of a State to handle next character to parse
   * @param c the next character to parse
   * @return a new parser-state
   */
  virtual auto handleCharacter(char c) -> ParserState * = 0;
};

#endif
