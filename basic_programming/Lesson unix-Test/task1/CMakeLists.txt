cmake_minimum_required(VERSION 3.5)
project(tests)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_executable(testN testMain.cpp extended_array.h forTest.h)
