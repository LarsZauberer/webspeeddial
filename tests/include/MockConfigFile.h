#ifndef MockConfigFile_h_INCLUDED
#define MockConfigFile_h_INCLUDED

#include "webspeeddial/IConfigFile.h"
#include "gmock/gmock.h"
class MockConfigFile : public core::IConfigFile {
    MOCK_METHOD(core::INode*, read, ());
    MOCK_METHOD(void, write, (core::INode*));
    MOCK_METHOD(bool, file_exists, ());
};

#endif // MockConfigFile_h_INCLUDED
