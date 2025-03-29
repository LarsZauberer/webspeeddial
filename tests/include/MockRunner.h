#include <gmock/gmock.h>

class MockRunner {
    public:
        MOCK_METHOD(FILE*, run, (), ());
        MOCK_METHOD(void, close, (), ());
};
