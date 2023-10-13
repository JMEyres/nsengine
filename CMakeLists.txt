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
	src/nsengine/Entity.cpp
	src/nsengine/Entity.h
	src/nsengine/Component.cpp
	src/nsengine/Component.h
)

target_link_libraries(demo nsengine)