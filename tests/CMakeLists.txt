add_executable(UnitTests
	unit_tests.hpp

	crt_memory_checker.hpp
	crt_memory_checker.cpp

	data_buffer_tests.cpp
	common_file_system_tests.cpp
)

target_link_libraries(UnitTests 
	PRIVATE
		BlocksGameCore

		Catch2::Catch2WithMain
)

set(TEST_RESOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources)
target_compile_definitions(UnitTests
	PRIVATE
		TEST_RESOURCE_DIRECTORY="${TEST_RESOURCE_DIRECTORY}"
)
