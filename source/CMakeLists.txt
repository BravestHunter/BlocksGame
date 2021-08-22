add_executable(Game
	game.cpp
)

target_link_libraries(Game 
	PRIVATE 
		glfw
		libglew_static
) 

