set(SOURCE_FILES
	op_result.hpp
	abstract_system.cpp
	abstract_system.hpp
	container.cpp
	container.hpp

	types.hpp
	direction.hpp
	camera_projection_type.hpp
	game.cpp
	game.hpp
	camera.cpp
	camera.hpp
	data_buffer.hpp

	utils/abstract_noise_2d.hpp
	utils/perlin_noise_2d.cpp
	utils/perlin_noise_2d.hpp

	log/abstract_log_system.hpp
	log/console_log_system.cpp
	log/console_log_system.hpp

	file/abstract_file_system.hpp
	file/common_file_system.cpp
	file/common_file_system.hpp

	resource/stb_headers.hpp
	resource/freetype_headers.hpp
	resource/resource_id.cpp
	resource/resource_id.hpp
	resource/image.hpp
	resource/glyph.hpp
	resource/abstract_font.hpp
	resource/freetype_font.cpp
	resource/freetype_font.hpp
	resource/abstract_resource_system.hpp
	resource/resource_system.cpp
	resource/resource_system.hpp

	world/block.hpp
	world/chunk_part.hpp
	world/chunk.hpp
	world/chunk_position.hpp
	world/chunk_storage.hpp
	world/world.cpp
	world/world.hpp

	window/abstract_window_system.hpp
	window/glfw_window_system.cpp
	window/glfw_window_system.hpp

	input/input.hpp
	input/keyboard_key_state.hpp
	input/keyboard_key.hpp
	input/abstract_input_system.hpp
	input/glfw/glfw_input.hpp
	input/glfw/glfw.hpp
	input/glfw/glfw_input_system.cpp
	input/glfw/glfw_input_system.hpp
	input/glfw/glfw_convert.cpp
	input/glfw/glfw_convert.hpp

	render/abstract_render_system.hpp
	render/glew/glew_headers.hpp
	render/glew/glew_entity.cpp
	render/glew/glew_entity.hpp
	render/glew/glew_texture.cpp
	render/glew/glew_texture.hpp
	render/glew/glew_glyph.cpp
	render/glew/glew_glyph.hpp
	render/glew/glew_render_system.cpp
	render/glew/glew_render_system.hpp
	render/glew/glew_chunks_map.hpp
	render/glew/glew_shader_type.hpp
	render/glew/glew_shader_program.cpp
	render/glew/glew_shader_program.hpp
	render/glew/glew_shader.cpp
	render/glew/glew_shader.hpp
	render/glew/glew_block_shader_program.cpp
	render/glew/glew_block_shader_program.hpp
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
		freetype
		FastNoise
) 

target_compile_definitions(BlocksGameCore
	PRIVATE
		RESOURCE_DIRECTORY="${RESOURCE_DIRECTORY}"
		SHADERS_DIRECTORY="${RESOURCE_DIRECTORY}/shaders"
		TEXTURES_DIRECTORY="${RESOURCE_DIRECTORY}/textures"
		FONTS_DIRECTORY="${RESOURCE_DIRECTORY}/fonts"
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
