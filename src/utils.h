/**@file utils.h This is a utils function file
 */
#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "concepts.h"
#include "config.h"
#include <string>

/**@brief `bookmarks_to_fzf` converts a `Buffer` of `BookMark*` to a syntax that
 * can be read by fuzzy finders
 * @tparam T A `Buffer` containing `BookMark*`
 * @param bookmarks A pointer to a `Buffer` containing `BookMark*`
 * @return Returns a `std::string` that can be used by a fuzzy finder.
 * @see Buffer
 * @see BookMark
 */
template <typename T>
  requires Buffer<T, BookMark *>
std::string bookmarks_to_fzf(T *bookmarks) {
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

/**@brief `find_name` takes a `Buffer` of `BookMark*` and searches for a
 * `BookMark` with a specific `name`.
 * @tparam T A `Buffer` containing `BookMark`
 * @param name The string name that is being searched for
 * @param arr A pointer to a `Buffer` containing `BookMark` where the `name` is
 * searched in`
 */
template <typename T>
  requires Buffer<T, BookMark *>
BookMark *find_name(std::string *name, T *arr) {
  if (!arr) {
    return NULL;
  }
  if (!name) {
    return NULL;
  }

  int n = arr->size();

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

/**
 * `remove_trailing` removes a trailing `\n` from a giving sting
 * @param str Is the string that needs is beeing stripped
 * @return It returns the pointer to the modified string
 */
std::string *remove_trailing(std::string *str);

#endif // utils_h_INCLUDED
