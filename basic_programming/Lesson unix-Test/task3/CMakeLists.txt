cmake_minimum_required(VERSION 3.5)
project(tests)
find_package(Catch2 3 REQUIRED)
add_executable(tests testTre.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)