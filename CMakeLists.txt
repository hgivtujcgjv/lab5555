cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab5555)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/banking)
        
  add_executable(test_acc tests/test_acc.cpp)
  add_executable(test_tr tests/test_tr.cpp)
  target_compile_options(test_acc PRIVATE --coverage)
  target_compile_options(test_tr PRIVATE --coverage)
  target_include_directories(test_acc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)
  target_include_directories(test_tr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)
  target_link_libraries(test_acc PRIVATE gtest_main gmock_main banking --coverage)
  target_link_libraries(test_tr PRIVATE gtest_main gmock_main banking --coverage)
