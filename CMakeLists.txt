﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("function_ref")

# Include sub-projects.
add_subdirectory(external/function_ref)
add_subdirectory ("function_ref")
