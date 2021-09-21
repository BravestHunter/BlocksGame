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
