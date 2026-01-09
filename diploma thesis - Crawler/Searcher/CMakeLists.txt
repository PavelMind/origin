cmake_minimum_required(VERSION 3.5)
project(Searcher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_ROOT "R:/Development/Library_and_framework/Boost/boost_1_88_0")
set(Boost_USE_STATIC_LIBS ON)
set(OPENSSL_ROOT_DIR "R:/Development/Library_and_framework/OpenSSL/openssl-3.4.2offsite")
set(OpenSSL_DIR "R:/Development/Library_and_framework/OpenSSL/openssl-3.4.2offsite/include/openssl")
set(libpqxx_DIR "R:/Development/Library_and_framework/libpq++/libpqxx-7.10.1")
set(httplib_DIR_Second "R:/Development/Library_and_framework/cpp-httplib/cpp-httplib-0.24.0")

file(GLOB_RECURSE DBfiles
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/sql builders/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data base/sql builders/*.h"
)
file(GLOB_RECURSE INIParsFiles
    "${CMAKE_CURRENT_SOURCE_DIR}/ini-parser/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/ini-parser/*.h"
)
file(GLOB_RECURSE InetFiles
    "${CMAKE_CURRENT_SOURCE_DIR}/internet/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internet/*.h"
)
include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}/data base" 
"${CMAKE_CURRENT_SOURCE_DIR}/internet"
"${CMAKE_CURRENT_SOURCE_DIR}/ini-parser")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/files/crawler_data.ini  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/files/main_crawler.html  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/files/cert.pem ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/files/key.pem ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


add_subdirectory(${libpqxx_DIR} libpqxx-build)
add_subdirectory(${httplib_DIR_Second} httplibbuildsec)
find_package (Boost COMPONENTS locale REQUIRED )
find_package(OpenSSL REQUIRED)
include_directories(${OpenSSL_DIR}) 



if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Searcher main.cpp ${DBfiles} ${INIParsFiles} ${InetFiles}
    "files/crawler_data.ini" 
    "files/main_crawler.html"
    )
    target_link_libraries(Searcher PRIVATE ${Boost_LIBRARIES} Boost::headers)
endif()

target_link_libraries(Searcher PRIVATE libpqxx::pqxx  ws2_32)
if (OpenSSL_FOUND)        
    set(OPENSSL_USE_STATIC_LIBS TRUE)
endif()
target_link_libraries (Searcher PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(Searcher PUBLIC ${httplib_DIR_Second})