#ifndef MockDelete_h_INCLUDED
#define MockDelete_h_INCLUDED

#include "gmock/gmock.h"
class MockDelete {
    public:
        MOCK_METHOD(void, foo, ());
};

#endif // MockDelete_h_INCLUDED
