set(SOURCE_FILES
	main.cpp

	op_result.hpp
	abstract_system.cpp
	abstract_system.hpp
	container.cpp
	container.hpp

	game.cpp
	game.hpp
	image.hpp
	camera.cpp
	camera.hpp
	shader.cpp
	shader.hpp

	file/abstract_file_system.hpp
	file/common_file_system.cpp
	file/common_file_system.hpp

	window/abstract_window_system.hpp
	window/glfw_window_system.cpp
	window/glfw_window_system.hpp

	input/key_state.hpp
	input/keyboard_key.hpp
	input/abstract_input_system.hpp
	input/glfw_input_system.cpp
	input/glfw_input_system.hpp
	input/glfw_convert.cpp
	input/glfw_convert.hpp

	render/abstract_render_system.hpp
	render/glew_render_system.cpp
	render/glew_render_system.hpp

	model/block.hpp
	model/chunk.hpp
	model/map.hpp
)

add_executable(BlocksGame
	${SOURCE_FILES}
)

target_include_directories(
	BlocksGame
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(BlocksGame 
	PRIVATE 
		glfw
		libglew_static
		stb
		glm
) 

target_compile_definitions(BlocksGame
	PRIVATE
		RESOURCE_DIRECTORY="${RESOURCE_DIRECTORY}"
		SHADERS_DIRECTORY="${RESOURCE_DIRECTORY}/shaders"
		TEXTURES_DIRECTORY="${RESOURCE_DIRECTORY}/textures"
)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
