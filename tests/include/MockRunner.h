#include "webspeeddial/File.h"
#include "webspeeddial/Runner.h"
#include <gmock/gmock.h>

class MockRunner : public core::Runner {
    public:
        MOCK_METHOD(core::File*, run, (), (override));
};
