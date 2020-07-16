#ifndef BIBPARSER_SRC_FILEWRITER_HPP_
#define BIBPARSER_SRC_FILEWRITER_HPP_

/**
 * A file writer interface
 */
struct FileWriter {

  /**
   * default destructor.
   */
  virtual ~FileWriter() = default;

  /**
   * Writes Contents to the write-target
   * @return success of the write-action
   * @note on success: writes a new file as side effect
   */
  virtual auto write() -> bool = 0;
};

#endif
