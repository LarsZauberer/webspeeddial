#include <string>

namespace core {

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

};
