#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "webspeeddial/concepts.h"
#include "webspeeddial/config.h"
#include <cstddef>
#include <string>

namespace core {
/**@brief A function that finds a bookmark in a Buffer
 * @tparam T A Buffer that carries a Bookmark
 * @param name The name that the Bookmark should carry
 * @param arr The array in which we should search
 * @return A pointer to the Bookmark found. If it is null no Bookmark was found
 */
template <typename T>
  requires Buffer<T, Bookmark>
Bookmark *find_bookmark(std::string &name, T &arr) {
  const size_t n = arr.size();
  for (size_t i = 0; i < n; i++) {
    Bookmark &ele = arr[i];
    if (ele.name == name) {
      return &ele;
    }
  }
  return nullptr;
}

/**@brief A function that unallocates everything from a given array
 * @tparam T A Buffer that carries pointers to a malloc object
 * @tparam D The pointer to an element on the heap
 * @param arr A reference to a Buffer with pointers to elements on the heap that will be unallocated afterwards
 */
template <typename T, typename D> requires Buffer<T, D*>
void unalloc_all(T& arr) {
    const size_t n = arr.size();
    for (size_t i = 0; i < n; i++) {
        if (arr[i]) {
            delete arr[i];
        }
        arr[i] = nullptr;
    } 
}

} // namespace core

#endif // utils_h_INCLUDED
