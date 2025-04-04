#ifndef MockClass_h_INCLUDED
#define MockClass_h_INCLUDED

#include <trompeloeil.hpp>

class MockClass {
    public:
        MAKE_MOCK0(foo, void()); 
};

#endif // MockClass_h_INCLUDED
