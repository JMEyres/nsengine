cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(NSENGINE)

include_directories(
	src
	contrib/windows-cl-amd64/SDL2/include
	contrib/windows-cl-amd64/glew/include
	contrib/windows-cl-amd64/stb/include
	contrib/windows-cl-amd64/ReactPhysics3D/include
	contrib/windows-cl-amd64/OpenAL/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/SDL2/lib
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/glew/lib
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/ReactPhysics3D/lib
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/OpenAL/lib
)

add_subdirectory(contrib/windows-cl-amd64/ReactPhysics3D)

add_library(rend
	src/rend/Animation.cpp
	src/rend/Animation.h
	src/rend/Buffer.cpp
	src/rend/Buffer.h
	src/rend/Debug.cpp
	src/rend/Debug.h
	src/rend/Exception.h
	src/rend/Face.h
	src/rend/Font.cpp
	src/rend/Font.h
	src/rend/glm
	src/rend/Mesh.cpp
	src/rend/Mesh.h
	src/rend/Model.cpp
	src/rend/Model.h
	src/rend/ModelShader.cpp
	src/rend/ModelShader.h
	src/rend/rend.h
	src/rend/Renderer.h
	src/rend/RenderTexture.cpp
	src/rend/RenderTexture.h
	src/rend/rendfltk.h
	src/rend/rendgl.h
	src/rend/rendmath.cpp
	src/rend/rendmath.h
	src/rend/rendsdl.h
	src/rend/Shader.cpp
	src/rend/Shader.h
	src/rend/stb_image.h
	src/rend/TextShader.cpp
	src/rend/TextShader.h
	src/rend/Texture.cpp
	src/rend/Texture.h
	src/rend/utils.cpp
	src/rend/utils.h
)
target_link_libraries(rend glew32 opengl32)


add_library(nsengine
	src/nsengine/nsengine.h
	src/nsengine/Core.cpp
	src/nsengine/Core.h
	src/nsengine/Camera.cpp
	src/nsengine/Camera.h
	src/nsengine/Entity.cpp
	src/nsengine/Entity.h
	src/nsengine/Component.cpp
	src/nsengine/Component.h
	src/nsengine/TriangleRenderer.cpp
	src/nsengine/TriangleRenderer.h
	src/nsengine/Resource.cpp
	src/nsengine/Resource.h
	src/nsengine/Resources.cpp
	src/nsengine/Resources.h
	src/nsengine/Transform.cpp
	src/nsengine/Transform.h
	src/nsengine/Environment.cpp
	src/nsengine/Environment.h
	src/nsengine/Input.cpp
	src/nsengine/Input.h
	src/nsengine/Texture.cpp
	src/nsengine/Texture.h
	src/nsengine/Model.cpp
	src/nsengine/Model.h
	src/nsengine/Renderer.cpp
	src/nsengine/Renderer.h
	src/nsengine/BoxCollider.cpp
	src/nsengine/BoxCollider.h
	src/nsengine/RigidBody.cpp
	src/nsengine/RigidBody.h
	src/nsengine/Audio.cpp
	src/nsengine/Audio.h
	src/nsengine/AudioSource.cpp
	src/nsengine/AudioSource.h
	src/nsengine/Gui.cpp
	src/nsengine/Gui.h
	src/nsengine/CapsuleCollider.cpp
	src/nsengine/CapsuleCollider.h
	src/nsengine/SpriteRenderer.cpp
	src/nsengine/SpriteRenderer.h
	)
	
set_property(TARGET nsengine PROPERTY CXX_STANDARD 17)
target_link_libraries(nsengine rend SDL2 ReactPhysics3D openal32)

add_executable(demo
	src/demo/blocks.h
	src/demo/controller.h
	src/demo/cameracontroller.h
	src/demo/main.cpp
)

set_property(TARGET demo PROPERTY CXX_STANDARD 17)
target_link_libraries(demo nsengine)