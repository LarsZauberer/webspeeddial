#ifndef MockRunner_h_INCLUDED
#define MockRunner_h_INCLUDED

#include "gmock/gmock.h"
#include <optional>
#include "MockFile.h"
class MockRunner {
    public:
        MOCK_METHOD(std::optional<MockFile>, run, (std::string&, std::string&)); 
};

#endif // MockRunner_h_INCLUDED
