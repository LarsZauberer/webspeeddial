#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "config.h"
#include <string>

std::string bookmarks_to_fzf (BookMark** bookmarks, size_t n);

BookMark *find_name(string *name, BookMark **arr, size_t n);

string *remove_trailing(string *str); 

#endif // utils_h_INCLUDED
