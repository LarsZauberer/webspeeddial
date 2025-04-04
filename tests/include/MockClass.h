#ifndef MockClass_h_INCLUDED
#define MockClass_h_INCLUDED

#include "gmock/gmock.h"
#include <gmock/gmock.h>

class MockClass {
    public:
        MOCK_METHOD(void, foo, ()); 
};

#endif // MockClass_h_INCLUDED
