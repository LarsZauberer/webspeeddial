#include <string.h>
#include "utils.h"

using std::string;

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
