#ifndef MockFile_h_INCLUDED
#define MockFile_h_INCLUDED

#include "webspeeddial/File.h"
#include "gmock/gmock.h"
class MockFile : public core::File {
public:
  MOCK_METHOD(char, read_c, ());
};

#endif // MockFile_h_INCLUDED
