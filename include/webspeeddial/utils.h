#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "webspeeddial/concepts.h"
#include "webspeeddial/config.h"
#include <cstddef>
#include <iostream>
#include <optional>
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

/**@brief Runs a command and gives back the output
 * @tparam T The runner that is used to run the cmd command
 * @tparam F The File descriptor that is output
 * @param cmd The command as a string
 * @param inp The input that is passed to the stdin of the command
 * @return The output of the command ran as an optional
 */
template <typename T, typename F> requires File<F> && Runner<T, F> 
std::string *run_cmd(T &runner, std::string& cmd, std::string& inp) {
    F *file = runner.run(cmd, inp); 

    if (!file) {
        std::cout << "Error while running the command: " << cmd << std::endl;
        return nullptr;
    }

    std::string *data = new std::string();
    data->reserve(64);

    int c;
    while (true) {
        c = file->read_c();
        if (c <= 0) {
            break;
        }
        *data = *data + (char) c;
    }

    delete file;

    return data;
}

} // namespace core

#endif // utils_h_INCLUDED
