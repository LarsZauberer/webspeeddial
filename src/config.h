#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <stdlib.h>

const size_t NAME_SIZE = 255;
const size_t RUNNER_SIZE = 255;
const size_t LINK_SIZE = 1024;

class BookMark {
    public:
        char name [NAME_SIZE];
        char link [LINK_SIZE];
};

class Config {
    public:
        char runner[NAME_SIZE];
        BookMark* bookmarks;
};

#endif // config_h_INCLUDED
