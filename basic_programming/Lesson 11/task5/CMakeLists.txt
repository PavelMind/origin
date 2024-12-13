cmake_minimum_required(VERSION 3.22.0)
project(projectTask3)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_executable(dunamicFigure main.cpp)
add_library (dunamicMyLib SHARED 
equiLatTriangle.h equiLatTriangle.cpp
figure.h figure.cpp
isoscelesTriangle.h isoscelesTriangle.cpp
parallelogram.h parallelogram.cpp
quadrangle.h quadrangle.cpp
rectangle.h rectangle.cpp
rhombus.h rhombus.cpp
rightTriangle.h rightTriangle.cpp
square.h square.cpp
triangle.h triangle.cpp
)
target_link_libraries(dunamicFigure dunamicMyLib)