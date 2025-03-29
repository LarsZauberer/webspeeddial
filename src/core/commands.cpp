#include "webspeeddial/commands.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>

std::string *copy_content_from_file(FILE *f) {
  if (!f) {
    return NULL;
  }
  // Read stdout from the file
  std::string *out = new std::string("");
  int c;
  while ((c = fgetc(f)) != -1) {
    *out += (char)c;
  }

  return out;
}
