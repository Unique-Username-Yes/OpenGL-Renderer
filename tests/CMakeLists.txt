project(MainTests)

add_executable(
  MainTests
  mainTests.cpp
)
target_link_libraries(
  MainTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MainTests)