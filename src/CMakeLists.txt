include(FetchContent)

FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
)

FetchContent_MakeAvailable(yaml-cpp)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(webspeeddial ${SOURCES})
target_include_directories(webspeeddial PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(webspeeddial yaml-cpp)
