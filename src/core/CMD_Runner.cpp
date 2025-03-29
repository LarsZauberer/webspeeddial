#include <iostream>
#include <optional>
#include "webspeeddial/CMD_File.h"
#include "webspeeddial/CMD_Runner.h"

namespace core {

std::optional<File> CMD_Runner::run() {
  FILE *f = popen(this->cmd->data(), "r");
  if (!f) {
    if (!this->err) {
      std::cout << this->err << std::endl;
    }
    return {};
  }
  CMD_File cmd_file = CMD_File(f);
  return cmd_file;
}

}; // namespace core
