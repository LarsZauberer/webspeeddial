#include "webspeeddial/File.h"
#include "webspeeddial/Runner.h"
#include <gmock/gmock.h>
#include <optional>

class MockRunner : public core::Runner {
    public:
        MOCK_METHOD(std::optional<core::File> , run, (), (override));
};
