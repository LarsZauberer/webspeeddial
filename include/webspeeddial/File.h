#ifndef File_h_INCLUDED
#define File_h_INCLUDED

namespace core {

/**@brief A wrapper class to describe some kind of file
 */

class File {
public:
  /**@brief A function that reads a char from a file
   */

  virtual char read_c() {return '\0';};
  virtual ~File() {};
};

}; // namespace core

#endif // File_h_INCLUDED
