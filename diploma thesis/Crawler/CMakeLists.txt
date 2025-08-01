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
include_directories(${Boost_INCLUDE_DIRS})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/crawler_data.ini  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(libpqxx_DIR "R:\\Development\\Library_and_framework\\libpq++\\libpqxx-7.10.1")
add_subdirectory(${libpqxx_DIR} libpqxx-build)

#find_package(libpqxx REQUIRED)
find_package (Boost COMPONENTS locale REQUIRED )
#find_package(Boost REQUIRED)
#find_package(Boost COMPONENTS system REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Crawler main.cpp ${DBfile} ${INIpars} ${TrdPool} "indexator/indexator.h" "indexator/indexator.cpp" "http_connect.h" "my_utilites.h" "my_utilites.cpp" 
    "iterateSite.h" "iterateSite.cpp" "crawler_data.ini")
    target_link_libraries(Crawler PRIVATE ${Boost_LIBRARIES} Boost::headers)
    
endif()
target_link_libraries(Crawler PRIVATE libpqxx::pqxx  ws2_32)