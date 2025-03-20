#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <stdlib.h>
#include <string>

using std::string;

class BookMark {
public:
  string name;
  string link;
};

class Config {
public:
  string runner;
  BookMark *bookmarks;
};

#endif // config_h_INCLUDED
