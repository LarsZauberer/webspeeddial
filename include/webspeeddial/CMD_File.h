#ifndef CMD_File_h_INCLUDED
#define CMD_File_h_INCLUDED

#include <cstdio>
#include <iostream>
namespace core {
/**@brief Class wrapping the file descriptor after running a cmd command
 */
class CMD_File {
public:
  CMD_File(FILE *f) : f(f) {};
  CMD_File(CMD_File &&file) {
    std::cout << "Moving CMD_File" << std::endl;
    this->f = file.f;
  };
  ~CMD_File() { if (f) delete f; };

  /**@brief Reads a character from the file descriptor
   * @returns The character from the filedescriptor
   */
  char read_c() {
    if (!f) {
      return '\0';
    }
    return fgetc(f);
  }

private:
  FILE *f;
};
} // namespace core

#endif // CMD_File_h_INCLUDED
