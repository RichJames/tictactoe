# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, test_main, gmock and gmock_main
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 )

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
	  	      "${gmock_SOURCE_DIR}/include")
endif()

include_directories(${TicTacToe_SOURCE_DIR}/include
		    ${TicTacToe_SOURCE_DIR}/src
	            /opt/lampp/include)
link_directories(${TicTacToe_SOURCE_DIR}/src)

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#	message(STATUS "dir='${dir}'")
#endforeach()
# Now simply link against gtest or gtest_main as needed. Eg
add_executable(io_redirects io_redirects.cpp)
target_link_libraries(io_redirects gtest_main)

add_executable(playertests $<TARGET_OBJECTS:game> player_unittests io_redirects)
target_link_libraries(playertests mysqlclient gtest_main)

add_executable(randgentests $<TARGET_OBJECTS:game> randomnumbergenerator_unittests)
target_link_libraries(randgentests mysqlclient gtest_main)

add_executable(boardtests $<TARGET_OBJECTS:game> board_unittests io_redirects)
target_link_libraries(boardtests mysqlclient gtest_main)

add_executable(inputtests input_unittests io_redirects)
target_link_libraries(inputtests gtest_main)

add_executable(playgametests $<TARGET_OBJECTS:game> play_game_unittests io_redirects)
target_link_libraries(playgametests mysqlclient gtest_main)

add_executable(gamepositiontest $<TARGET_OBJECTS:game> test_game_positions)
target_link_libraries(gamepositiontest mysqlclient gtest_main)

#add_test(NAME io_redirects_test COMMAND io_redirects)
#add_test(NAME player_test COMMAND playertests)

#add_test(NAME io_redirects_test COMMAND io_redirects)
#add_test(NAME player_test COMMAND playertests)
