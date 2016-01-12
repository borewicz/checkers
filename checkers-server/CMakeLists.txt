cmake_minimum_required(VERSION 3.3)
project(checkers_server)
 
#add_subdirectory(network)
#add_subdirectory(jsonParser)
#add_subdirectory(game)
#add_subdirectory(eventService)

file(GLOB_RECURSE SOURCES
		"*.h"
		"*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.45.0 COMPONENTS system thread) 
include_directories(${Boost_INCLUDE_DIRS}) 
add_library(checkers_lib ${SOURCES})
add_executable(checkers_server main.cpp)
target_link_libraries(checkers_server checkers_lib ${Boost_LIBRARIES})

