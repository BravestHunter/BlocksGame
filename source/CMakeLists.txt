set(SOURCE_FILES
	main.cpp

	game.cpp
	game.hpp
	shader.cpp
	shader.hpp
)

add_executable(BlocksGame
	${SOURCE_FILES}
)

target_link_libraries(BlocksGame 
	PRIVATE 
		glfw
		libglew_static
		stb
) 

target_compile_definitions(BlocksGame
	PRIVATE
		RESOURCE_DIRECTORY="${RESOURCE_DIRECTORY}"
		SHADERS_DIRECTORY="${RESOURCE_DIRECTORY}/shaders"
)
