#include "utils.h"
#include "config.h"
#include <cstddef>
#include <string>

using std::string;

string bookmarks_to_fzf(BookMark **bookmarks, size_t n) {
  if (!bookmarks) {
    return "";
  }
  string res = "";
  for (size_t i = 0; i < n; i++) {
    if (!*bookmarks)
      break;

    if (i == n - 1) {
      // Last element
      res += bookmarks[i]->name;
      continue;
    }

    res += bookmarks[i]->name + "\n";
  }

  return res;
}

/// This searches an element in an pointer array. It compares pointers not the
/// element contents.
BookMark *find_name(string *name, BookMark **arr, size_t n) {
  if (!arr) {
    return NULL;
  }
  if (!name) {
    return NULL;
  }
  for (size_t i = 0; i < n; i++) {
    if ((*name).compare(arr[i]->name) == 0) { // Check if equal
      return arr[i];
    }
  }
  return NULL;
}

