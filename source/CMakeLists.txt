set(SOURCE_FILES
	op_result.hpp
	abstract_system.cpp
	abstract_system.hpp
	container.cpp
	container.hpp

	types.hpp
	game.cpp
	game.hpp
	image.hpp
	camera.cpp
	camera.hpp
	data_buffer.hpp

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
	render/glew/glew.hpp
	render/glew/glew_render_system.cpp
	render/glew/glew_render_system.hpp
	render/glew/glew_shader_type.hpp
	render/glew/glew_shader_program.cpp
	render/glew/glew_shader_program.hpp
	render/glew/glew_shader.cpp
	render/glew/glew_shader.hpp

	model/block.hpp
	model/chunk.hpp
	model/map.hpp
)

add_library(BlocksGameCore STATIC ${SOURCE_FILES})

target_include_directories(BlocksGameCore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
#target_include_directories(BlocksGameCore
#    PUBLIC
#        ${PROJECT_BINARY_DIR}/source/config
#)
target_include_directories(BlocksGameCore
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(BlocksGameCore 
	PUBLIC
		glfw
		libglew_static
		stb
		glm
) 

target_compile_definitions(BlocksGameCore
	PRIVATE
		RESOURCE_DIRECTORY="${RESOURCE_DIRECTORY}"
		SHADERS_DIRECTORY="${RESOURCE_DIRECTORY}/shaders"
		TEXTURES_DIRECTORY="${RESOURCE_DIRECTORY}/textures"
)


add_executable(BlocksGame
	main.cpp
)

#target_include_directories(
#	BlocksGame
#		PRIVATE
#			${CMAKE_CURRENT_SOURCE_DIR}
#)

target_link_libraries(BlocksGame 
	PRIVATE
		BlocksGameCore
) 


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
