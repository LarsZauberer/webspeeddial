#ifndef MockFile_h_INCLUDED
#define MockFile_h_INCLUDED

#include <string>
class MockFile {
public:
  MockFile(std::string data) : data(data) {};

  char read_c() {
      if (index >= data.size()) {
          return '\0';
      }
    return data[index++];
  }
private:
  std::string data;
  size_t index = 0;
};

#endif // MockFile_h_INCLUDED
