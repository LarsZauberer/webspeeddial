/**@file commands.h All functions handling system command callings
 */
#ifndef commands_h_INCLUDED
#define commands_h_INCLUDED

#include <cstdio>
#include <string>
#include "concepts.h"

/**@brief Returns the content of a `FILE*` descriptor as a string
 * @param f A pointer to a `FILE`
 * @return A string with the content of `f`
 * @note The string needs to be deallocated
 */
std::string *copy_content_from_file(FILE *f);

/**@brief Runs a command and returns the file descriptor
 * @tparam T A `CMD_Runner`
 * @param runner A pointer to a `CMD_Runner`
 * @return A file descriptor to the command run
 * @see CMD_Runner
 * @note The string needs to be deallocated
 */
template <CMD_Runner T>
std::string* run_cmd(T *runner) {
    // NULL Checker
    if (!runner) {
        return NULL;
    }

    FILE *f = runner->run();
    std::string *out = copy_content_from_file(f);

    // Cleanup
    runner->close();
    f = NULL;

    return out;
};

#endif // commands_h_INCLUDED
