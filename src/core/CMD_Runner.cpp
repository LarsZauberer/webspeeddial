#include <iostream>
#include "webspeeddial/CMD_File.h"
#include "webspeeddial/CMD_Runner.h"

namespace core {

File *CMD_Runner::run() {
  FILE *f = popen(this->cmd->data(), "r");
  if (!f) {
    if (!this->err) {
      std::cout << this->err << std::endl;
    }
    return NULL;
  }
  CMD_File *cmd_file = new CMD_File(f);
  return cmd_file;
}

}; // namespace core
