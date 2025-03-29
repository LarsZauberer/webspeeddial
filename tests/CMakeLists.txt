include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
file(GLOB TEST_SOURCES *.cpp)

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests gtest_main core)

include(GoogleTest)
gtest_discover_tests(runTests)
