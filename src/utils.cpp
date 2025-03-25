#include "utils.h"
#include "config.h"
#include <cstddef>
#include <string>
#include <vector>

using std::string;

template<typename T> requires Buffer<T, BookMark*>
string bookmarks_to_fzf(T *bookmarks, size_t n) {
  if (!bookmarks) {
    return "";
  }
  string res = "";
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

/// This searches an element in an pointer array. It compares pointers not the
/// element contents.
template<typename T> requires Buffer<T, BookMark*>
BookMark *find_name(string *name, T *arr, size_t n) {
  if (!arr) {
    return NULL;
  }
  if (!name) {
    return NULL;
  }
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

string *remove_trailing(string *str) {
    if (!str) {
        return NULL;
    }
    size_t pos = (*str).rfind("\n");

    if (pos == ((size_t) -1)) {
        // No match found
        return str;
    }

    (*str).erase(pos);

    return str;
}

template string bookmarks_to_fzf(std::vector<BookMark*>*, size_t);

template BookMark *find_name(string*, std::vector<BookMark*>*, size_t);
