# CMakeList.txt : CMake project for function_ref, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (function_ref "main.cpp" )

# TODO: Add tests and install targets if needed.
target_link_libraries(
	function_ref
	PRIVATE
	function-ref)
