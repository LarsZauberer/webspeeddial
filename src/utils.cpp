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
