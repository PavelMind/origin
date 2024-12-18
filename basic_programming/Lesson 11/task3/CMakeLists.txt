cmake_minimum_required(VERSION 3.22.0)
project(projectTask3)
add_executable(dunamicCMake client.cpp)

add_library (dunamicMyLib SHARED dunamo.h dunamo.cpp)
target_compile_definitions(dunamicMyLib PRIVATE LEAVER_EXPORTS)
target_link_libraries(dunamicCMake dunamicMyLib)