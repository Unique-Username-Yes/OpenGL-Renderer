cmake_minimum_required(VERSION 3.16)
project(OGLRenderer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

if(googletest_POPULATED)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(project)

