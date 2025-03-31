#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "webspeeddial/Config.h"
#include "webspeeddial/Runner.h"
#include "webspeeddial/File.h"

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

std::string bookmarks_to_fzf(std::vector<BookMark*>  *bookmarks) {
  if (!bookmarks) {
    return "";
  }

  size_t n = bookmarks->size();
  std::string res = "";

  for (size_t i = 0; i < n; i++) {
    if (!(*bookmarks)[i])
      break;

    if (i == n - 1) {
      // Last element
      res += (*bookmarks)[i]->name;
      continue;
    }

    res += (*bookmarks)[i]->name + "\n";
  }

  return res;
}

BookMark *find_name(std::string *name, std::vector<BookMark*> *arr) {
  if (!arr) {
    return NULL;
  }
  if (!name) {
    return NULL;
  }

  size_t n = arr->size();

  for (size_t i = 0; i < n; i++) {
    if (!(*arr)[i]) {
      continue;
    }
    if ((*name).compare((*arr)[i]->name) == 0) { // Check if equal
      return (*arr)[i];
    }
  }
  return NULL;
}

std::string copy_content_from_file(File *f) {
  if (!f) {
    return "";
  }
  // Read stdout from the file
  std::string out = std::string("");
  int c;
  while ((c = f->read_c()) > 0) {
    // std::cout << c << ": " << (char) c << std::endl;
    out += (char)c;
  }

  return out;
};

std::string run_cmd(Runner *runner) {
  // NULL Checker
  if (!runner) {
    return "";
  }

  File *f = runner->run();

  if (!f) {
    return "";
  }

  std::string out = copy_content_from_file(f);
  delete f;

  return out;
};

}; // namespace core
