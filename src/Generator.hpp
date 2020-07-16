#ifndef BIBPARSER_SRC_GENERATOR_HPP_
#define BIBPARSER_SRC_GENERATOR_HPP_

/**
 * A file writer interface
 */
struct Generator {

  /**
   * default destructor.
   */
  virtual ~Generator() = default;

  /**
   * Writes Contents to the write-target
   * @return success of the write-action
   * @note on success: writes a new file as side effect
   */
  virtual auto write() const -> std::string = 0;
};

#endif
