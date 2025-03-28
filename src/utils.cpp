#include <string.h>
#include "utils.h"

/**
 * `remove_trailing` removes a trailing `\n` from a giving sting
 * @param str Is the string that needs is beeing stripped
 * @return It returns the pointer to the modified string
 */
std::string *remove_trailing(std::string *str) {
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
