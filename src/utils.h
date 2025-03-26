#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "config.h"
#include <string>
#include "concepts.h"

template<typename T> requires Buffer<T, BookMark*>
string bookmarks_to_fzf (T *bookmarks, size_t n) {
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

string *remove_trailing(string *str);

#endif // utils_h_INCLUDED
