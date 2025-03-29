/**@file Runner.h Describes a `CMD_Runner` that runs commands in the terminal
 */

#ifndef Runner_h_INCLUDED
#define Runner_h_INCLUDED

#include <string>

namespace core {
/**@brief A CMD_Runner to run system commands
 */

class Runner {
public:
  /**@brief Constructs a Runner object from a `cmd` and an `err` message pointer
   * @param cmd Pointer to the command string
   * @param err Pointer to error message string (default: `NULL`)
   */

  Runner(std::string *cmd, std::string *err = NULL) : cmd(cmd), err(err) {};

  /**@brief Runs the command and returns the corresponding file descriptor
   * @return Returns the file descriptor containing the stdout of the command
   * ran.
   */

  FILE *run();

  /**@brief Closes the file descriptor of the command ran
   * If the command hasn't been run, the function won't do anything
   */

  void close();

private:
  std::string *cmd;
  std::string *err;
  FILE *f;
};

}; // namespace core

#endif // Runner_h_INCLUDED
