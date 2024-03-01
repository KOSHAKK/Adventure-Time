cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME SimpleGame)
project(${PROJECT_NAME})

add_executable(SimpleGame 
	src/main.cpp
	
	src/Resources/ResourceManager.hpp
	src/Render/ShaderProgram.hpp
	src/Render/Sprite.hpp
	src/Render/AnimatedSprite.hpp
	src/Render/Texture2D.hpp
	

	src/Render/ShaderProgram.cpp
	src/Render/Sprite.cpp
	src/Render/AnimatedSprite.cpp
	src/Render/Texture2D.cpp
	src/Resources/ResourceManager.cpp
	
	
	
	src/Game/Game.hpp
	src/Game/Game.cpp
	src/Game/IGameObject.hpp
	src/Game/IGameObject.cpp
	src/Game/ILevel.hpp
	src/Game/ILevel.cpp
	src/Game/Border.hpp
	src/Game/Border.cpp
	src/Game/CopperBlock.hpp
	src/Game/CopperBlock.cpp
	
	src/Game/Level_1.cpp
	src/Game/Level_1.hpp
	
	src/Game/MyceliumBlock.hpp
	src/Game/MyceliumBlock.cpp
	src/Game/NinjaFrog.hpp
	src/Game/NinjaFrog.cpp
	
	src/Physics/PhysicsEngine.hpp
	src/Physics/PhysicsEngine.cpp
	
	src/System/Keys.hpp
	src/System/KeyState.cpp
	src/System/KeyState.hpp
	
	# lib
	src/Resources/stb_image.hpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


include_directories(external/glm)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)