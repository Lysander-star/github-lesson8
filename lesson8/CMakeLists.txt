cmake_minimum_required(VERSION 3.10)
project(lengths CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lengths STATIC src/lengths.cpp)
target_include_directories(lengths PUBLIC include)

add_executable(test_lengths test/test_lengths.cpp)
target_link_libraries(test_lengths PRIVATE lengths)
