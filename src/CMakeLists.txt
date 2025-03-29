include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG        0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)

file(GLOB_RECURSE CORES core/*.cpp)
file(GLOB_RECURSE MAIN main/*.cpp)

add_library(core STATIC ${CORES})
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(core PUBLIC yaml-cpp)

add_executable(webspeeddial ${MAIN})
target_include_directories(webspeeddial PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(webspeeddial PUBLIC core)
