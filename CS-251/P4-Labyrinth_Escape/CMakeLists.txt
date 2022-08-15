cmake_minimum_required(VERSION 3.14)
project(P4-Labyrinth_Escape)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/c9461a9b55ba954df0489bab6420eb297bed846b.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tests
  tests.cpp
)
target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_executable(ExploreTheRegularLabyrinth ExploreTheRegularLabyrinth.cpp)
add_executable(ExploreTheTwistyLabyrinth ExploreTheTwistyLabyrinth.cpp)


