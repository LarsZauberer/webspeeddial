#ifndef utils_h_INCLUDED
#define utils_h_INCLUDED

#include "config.h"
#include <string>
#include "concepts.h"

template<typename T> requires Buffer<T, BookMark*>
string bookmarks_to_fzf (T *bookmarks, size_t n);

template<typename T> requires Buffer<T, BookMark*>
BookMark *find_name(string *name, T *arr, size_t n);

string *remove_trailing(string *str); 

#endif // utils_h_INCLUDED
