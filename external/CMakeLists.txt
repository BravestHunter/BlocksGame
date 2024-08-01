add_subdirectory(glfw)
add_subdirectory(glew)
add_subdirectory(stb)
add_subdirectory(glm)
add_subdirectory(freetype)

set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Disable Noise2Tool" FORCE)
set(FASTNOISE2_TESTS OFF CACHE BOOL "Disable Noise2Tests" FORCE)
add_subdirectory(fastnoise2)

add_subdirectory(catch2)
