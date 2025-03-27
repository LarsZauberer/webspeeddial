#include "commands.h"
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>

FILE *cmd_file(std::string* cmd,
              std::string* err) {
  if (!cmd) {
      return NULL;
  }
  // Open the selector
  FILE *pipe(popen((*cmd).data(), "r"));
  if (!pipe) {
    if (!err) {
        std::cout << *err 
                  << std::endl;
    }
    return NULL;
  }
  return pipe;
}

std::string copy_content_from_file(FILE *f) {
  if (!f) {
    return "";
  }
  // Read stdout from the file
  std::string out = "";
  out.reserve(128);
  char c;
  while (c != EOF) {
    c = fgetc(f);
    out += c;
  }

  return out;
}

std::string run_cmd(std::string* cmd, std::string* err) {
    if (!cmd) {
        return "";
    }

    FILE* file = cmd_file(cmd, err);
    std::string out = copy_content_from_file(file); 
    fclose(file);
    return out;
}
