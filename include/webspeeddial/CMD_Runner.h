#ifndef CMD_Runner_h_INCLUDED
#define CMD_Runner_h_INCLUDED

#include "webspeeddial/File.h"
#include "webspeeddial/Runner.h"
#include <optional>
#include <string>

namespace core {

/**@brief A class describing a runner that runs cmd programs
 */


class CMD_Runner : public Runner {
public:
  /**@brief Constructs a Runner object from a `cmd` and an `err` message pointer
   * @param cmd Pointer to the command string
   * @param err Pointer to error message string (default: `NULL`)
   */

  CMD_Runner(std::string *cmd, std::string *err = NULL) : cmd(cmd), err(err) {};

  /**@brief Runs the command and returns the corresponding file descriptor
   * @return Returns the file descriptor containing the stdout of the command
   * ran.
   */

  std::optional<File> run();

  /**@brief Closes the file descriptor of the command ran
   * If the command hasn't been run, the function won't do anything
   */

private:
  std::string *cmd;
  std::string *err;
};

};

#endif // CMD_Runner_h_INCLUDED
