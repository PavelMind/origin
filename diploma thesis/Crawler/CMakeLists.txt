cmake_minimum_required(VERSION 3.20)
project(Crawler)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_ROOT "R:/Development/Library_and_framework/Boost/boost_1_88_0")
set(Boost_USE_STATIC_LIBS ON)
#set(CMAKE_PREFIX_PATH "R:/Development/Library_and_framework/Boost/boost_1_88_0")
#set(CMAKE_MODULE_PATH  "R:/Development/Library_and_framework/Boost/boost_1_88_0")
#set(Boost_INCLUDE_DIRS  "R:/Development/Library_and_framework/Boost/boost_1_88_0")

file(GLOB_RECURSE DBfile
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/*.h"
)
file(GLOB_RECURSE INIpars
    "${CMAKE_CURRENT_SOURCE_DIR}/ini-parser/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/ini-parser/*.h"
)
file(GLOB_RECURSE TrdPool
    "${CMAKE_CURRENT_SOURCE_DIR}/threads pool/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/threads pool/*.h"
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/data base")
include_directories("$ENV{VCPKG}/libpqxx/src/7.10.0-a5d32b19bc.clean/include" )
include_directories(${Boost_INCLUDE_DIRS})
#message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
#message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "file ini: ${CMAKE_CURRENT_SOURCE_DIR}/crawler_data.ini")
install(FILES "crawler_data.ini" DESTINATION .) 

find_package(libpqxx REQUIRED)
find_package (Boost COMPONENTS locale REQUIRED )
#find_package(Boost REQUIRED)

#find_package(Boost COMPONENTS system asio REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Crawler main.cpp ${DBfile} ${INIpars} ${INIpars} "indexator/indexator.h" "indexator/indexator.cpp" "http_connect.h" "my_utilites.h" "my_utilites.cpp" "crawler_data.ini")
    target_link_libraries(Crawler PRIVATE ${Boost_LIBRARIES} Boost::headers)
    
endif()
target_link_libraries(Crawler PRIVATE libpqxx::pqxx  ws2_32)