cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

project("TicTacToe")

#enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
endif()
if (NOT_CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

include_directories(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(cmake/GitUtils.cmake)
git_clone(
	PROJECT_NAME	googletest
	GIT_URL		https://github.com/google/googletest.git
	GIT_BRANCH	master
	)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(build/googletest)
