include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG        0.8.0
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(yaml-cpp)

# Test executable
file(GLOB TEST_SOURCES *.cpp)

add_executable(runTests ${TEST_SOURCES})
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(runTests gtest_main gmock_main core yaml-cpp)

include(GoogleTest)
gtest_discover_tests(runTests)
