#ifndef commands_h_INCLUDED
#define commands_h_INCLUDED

#include <cstdio>
#include <string>

// Testable
std::string copy_content_from_file(FILE *f);

// UnTestable
FILE *cmd_file(std::string *cmd, std::string *err = NULL);
std::string run_cmd(std::string *cmd, std::string *err = NULL);

#endif // commands_h_INCLUDED
