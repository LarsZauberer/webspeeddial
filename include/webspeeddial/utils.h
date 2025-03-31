/**@file utils.h This is a utils function file
 */
#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "webspeeddial/Config.h"
#include "webspeeddial/File.h"
#include "webspeeddial/Runner.h"
#include <string>
#include <vector>

namespace core {

/**@brief `bookmarks_to_fzf` converts a `Buffer` of `BookMark*` to a syntax that
 * can be read by fuzzy finders
 * @tparam T A `Buffer` containing `BookMark*`
 * @param bookmarks A pointer to a `Buffer` containing `BookMark*`
 * @return Returns a `std::string` that can be used by a fuzzy finder.
 * @see Buffer
 * @see BookMark
 */
std::string bookmarks_to_fzf(std::vector<BookMark *> *bookmarks);

/**@brief `find_name` takes a `Buffer` of `BookMark*` and searches for a
 * `BookMark` with a specific `name`.
 * @tparam T A `Buffer` containing `BookMark`
 * @param name The string name that is being searched for
 * @param arr A pointer to a `Buffer` containing `BookMark` where the `name` is
 * searched in`
 */
BookMark *find_name(std::string *name, std::vector<BookMark *> *arr);

/**
 * `remove_trailing` removes a trailing `\n` from a giving sting
 * @param str Is the string that needs is beeing stripped
 * @return It returns the pointer to the modified string
 */
std::string *remove_trailing(std::string *str);

/**@brief Returns the content of a `FILE*` descriptor as a string
 * @param f A pointer to a `FILE`
 * @return A string with the content of `f`
 * @note The string needs to be deallocated
 */
std::string copy_content_from_file(File *f);

/**@brief Runs a command and returns the file descriptor
 * @tparam T A `CMD_Runner`
 * @tparam F A `ReadableFile` that the CMD_Runner will return
 * @param runner A pointer to a `CMD_Runner`
 * @return A file descriptor to the command run
 * @see CMD_Runner
 * @note The string needs to be deallocated
 */
std::string run_cmd(Runner *runner);

/**@brief Pointer list cleanup
 * @tparam T The type of the object that will be deleted
 */
template <typename T> void unalloc_all(std::vector<T*> &arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        T *ele = arr[i];
        if (ele) delete ele;
    }
}

}; // namespace core

#endif // utils_h_INCLUDED
