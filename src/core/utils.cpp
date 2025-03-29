#include <string>

namespace core {

std::string *remove_trailing(std::string *str) {
  if (!str) {
    return NULL;
  }
  size_t pos = (*str).rfind("\n");

  if (pos == ((size_t)-1)) {
    // No match found
    return str;
  }

  (*str).erase(pos);

  return str;
}

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

}; // namespace core
