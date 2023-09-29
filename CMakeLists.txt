cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(NSENGINE)

include_directories(
	src
)

add_executable(demo
	src/demo/player.h
	src/demo/main.cpp
)

add_library(nsengine
	src/nsengine/Core.cpp
	src/nsengine/Core.h
)
