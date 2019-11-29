cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
project("TicTacToe")

#enable_testing()
set(cpp_standard "-std=c++17")
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cpp_standard}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
		    /opt/lampp/include)

#add_subdirectory(ToDoCore)

add_executable(
	tictactoe
	main.cpp
	play_game.cpp
	randomnumbergenerator.cpp
	board.cpp
	player.cpp
	)
target_link_libraries(tictactoe mysqlclient)

#add_test(ToDoTest ToDo)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
