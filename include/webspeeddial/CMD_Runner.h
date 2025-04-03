#ifndef CMD_Runner_h_INCLUDED
#define CMD_Runner_h_INCLUDED

#include "webspeeddial/CMD_File.h"
#include <cstdio>
#include <iostream>
#include <string>
namespace core {
/**@brief A runner that runs commands on the system
 */
class CMD_Runner {
public:
  CMD_Runner() = default;
  // CMD_Runner(CMD_Runner &&other) {
  //   std::cout << "CMD_Runner moved" << std::endl;
  // };

  /**@brief Runs a command with given input
   * @param cmd The command being executed
   * @param input The input passed to the stdin for the command
   * @return A CMD_File which is allocated on the head
   * @note The returned pointer has to be deallocated in the end
   */
  CMD_File *run(std::string &cmd, std::string &input) {
    std::string command = "echo '" + input + "' | " + cmd;
    FILE *f = popen(command.data(), "r");
    if (!f) {
      std::cout << "Error while executing command: " << command << std::endl;
      return nullptr;
    }
    return new CMD_File(f);
  }
};
}; // namespace core

#endif // CMD_Runner_h_INCLUDED
