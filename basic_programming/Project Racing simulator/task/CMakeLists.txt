cmake_minimum_required(VERSION 3.22.0)
project(RacingSimulator)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories(GameRacing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/transport/included)
include_directories(GameRacing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/track)
set(GLOB LIB-CPP ${CMAKE_CURRENT_SOURCE_DIR}/other/*.cpp) #не работает, при включении в add_library даёт ошибку/not work
add_library(TransportLib SHARED 
"track/track.cpp" "track/track.h" 
"track/airTrack.cpp" "track/airTrack.h" 
"track/groundTrack.cpp" "track/groundTrack.h" 
"track/allTrack.cpp" "track/allTrack.h" 
"transport/cppishki/camel.cpp" "transport/included/camel.h" 
"transport/cppishki/eagle.cpp" "transport/included/eagle.h" 
"transport/cppishki/carpet.cpp" "transport/included/carpet.h" 
"transport/cppishki/broom.cpp" "transport/included/broom.h" 
"transport/cppishki/camelFast.cpp" "transport/included/camelFast.h" 
"transport/cppishki/centaur.cpp" "transport/included/centaur.h" 
"transport/cppishki/boots.cpp"  "transport/included/boots.h" 
"transport/cppishki/baseTransport.cpp" "transport/included/baseTransport.h" 
"transport/cppishki/airTransport.cpp" "transport/included/airTransport.h" 
"transport/cppishki/groungTransport.cpp" "transport/included/groungTransport.h"  
"other/resultRace.cpp" "other/resultRace.h")
add_executable(GameRacing main.cpp  )
target_link_libraries(GameRacing TransportLib)
