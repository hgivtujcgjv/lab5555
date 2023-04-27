cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

option(BUILD_TEST "Build tests" ON)
project(lab5555)

add_library(banking banking/Account.cpp banking/Transaction.cpp)
target_include_directories(banking PUBLIC banking/)


if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(googletest)
  add_executable(check tests/test.cpp)
  target_link_libraries(check banking gtest_main gmock_main)
  add_test(NAME check COMMAND check)
endif()
