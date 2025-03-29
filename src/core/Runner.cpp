#include "webspeeddial/Runner.h"
#include "webspeeddial/CMD_FILE.h"
#include <cstdio>
#include <iostream>

namespace core {

std::optional<CMD_File> Runner::run() {
  FILE *f = popen(this->cmd->data(), "r");
  if (!f) {
    if (!this->err) {
      std::cout << this->err << std::endl;
    }
    return {};
  }
  return {CMD_File(f)};
}

}; // namespace core
