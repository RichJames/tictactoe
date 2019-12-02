set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES play_game.cpp randomnumbergenerator.cpp board.cpp player.cpp)

include_directories(${TicTacToe_SOURCE_DIR}/include
            /opt/lampp/include
            )

add_library(game OBJECT "${SOURCES}")
add_library("${BINARY}_lib" STATIC "${SOURCES}")
add_executable("${BINARY}" $<TARGET_OBJECTS:game> main.cpp)

target_link_libraries("${BINARY}" mysqlclient)
target_link_libraries("${BINARY}_lib" mysqlclient)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
