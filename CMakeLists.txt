cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(NSENGINE)

include_directories(
	src
	contrib/windows-cl-amd64/SDL2/include
	contrib/windows-cl-amd64/glew/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/SDL2/lib
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/glew/lib
)

add_library(rend
 src/rend/Animation.cpp
 src/rend/Buffer.cpp
 src/rend/Mesh.cpp
 src/rend/Model.cpp
 #src/rend/ModelRenderer.cpp
 src/rend/RenderTexture.cpp
 #src/rend/Renderer.cpp
 src/rend/Shader.cpp
 src/rend/Texture.cpp
 src/rend/rendmath.cpp
)

target_link_libraries(rend glew32)

add_library(nsengine
	src/nsengine/Core.cpp
	src/nsengine/Core.h
	src/nsengine/Entity.cpp
	src/nsengine/Entity.h
	src/nsengine/Component.cpp
	src/nsengine/Component.h
)

target_link_libraries(nsengine rend SDL2)

add_executable(demo
	src/demo/player.h
	src/demo/main.cpp
)


target_link_libraries(demo nsengine)