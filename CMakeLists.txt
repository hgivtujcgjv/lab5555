cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)
option(BUILD_TESTS "build" ON)

include_directories(banking)
add_subdirectory(Gtest/googletest)
add_library(banking STATIC
        banking/Account.cpp
        banking/Transaction.cpp)
        
if(BUILD_TESTS)
  enable_testing()
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(tests tests/test1.cpp)
  target_compile_options(tests PRIVATE --coverage)
  target_link_libraries(tests PRIVATE gtest_main --coverage)
endif()
