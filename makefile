#LDFLAGS="-L/opt/lampp/lib"
PROJ_DIR=.
INCLUDES=-I./include
COMPILER="clang++-9"
#COMPILER="g++"
DEBUG=-g
CFLAGS=-iquote$(PROJ_DIR)
GTEST_CFLAGS=`pkg-config --cflags gtest_main`
GTEST_LIBS=`pkg-config --libs gtest_main`
GMOCK_LIBS=`pkg-config --libs gmock`
OBJS = main.o play_game.o randomnumbergenerator.o board.o player.o
TESTOBJS = randomtests.o inputtests.o boardtests.o playertests.o playgametests.o player.o board.o \
	   randomnumbergenerator.o play_game.o io_redirects.o gamepositiontest.o
 
VPATH = src:tests:../include:./include

makeandtest: tictactoe testit

tictactoe: $(OBJS)
	${COMPILER}  ${DEBUG} -o $@ $^  ${LDFLAGS} -lmysqlclient

main.o : main.cpp play_game.h
	${COMPILER}  -c ${DEBUG} -o $@  $< $(INCLUDES) -I/opt/lampp/include -std=c++17
	
play_game.o : play_game.cpp play_game.h
	${COMPILER} -c ${DEBUG} -o $@ $< $(INCLUDES) -I/opt/lampp/include -std=c++17

randomnumbergenerator.o : randomnumbergenerator.cpp RandomNumberGenerator.h
	${COMPILER}  -c ${DEBUG} -o $@ $< $(INCLUDES) -std=c++17
	
board.o : board.cpp board.h
	${COMPILER}  -c ${DEBUG} -o $@ $< $(INCLUDES) -I/opt/lampp/include -std=c++17 

player.o : player.cpp player.h input.h
	${COMPILER}  -c ${DEBUG} -o $@ $< $(INCLUDES) -I/opt/lampp/include -std=c++17 

boardtests.o : board_unittests.cpp board.h io_redirects.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

playertests.o : player_unittests.cpp player.h input.h io_redirects.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

inputtests.o : input_unittests.cpp input.h io_redirects.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

randomtests.o : randomnumbergenerator_unittests.cpp RandomNumberGenerator.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

gamepositiontest.o : test_game_positions.cpp test_game_positions.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

io_redirects.o : io_redirects.cpp io_redirects.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

playgametests.o : play_game_unittests.cpp play_game.h io_redirects.h board.h
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} $(INCLUDES) -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

testit : $(TESTOBJS)
	${COMPILER} ${CXXFLAGS} ${LDFLAGS} $^ -v -o $@ ${GTEST_LIBS} ${GMOCK_LIBS} -lmysqlclient
	mv $@ tests/
	cp tests/tests.dat .
	tests/$@
	rm tests.dat

clean:
	- rm testmysql inputtest a.out *.o *tidy.txt *.gz

realclean:
	- rm testmysql a.out *.o tictactoe tests/testit

maintidy:
	clang-tidy-9 --header-filter='.h' --extra-arg='-std=c++17' main.cpp > maintidy.txt

boardtidy:
	clang-tidy-9 --header-filter='.h' --extra-arg='-std=c++17' board.cpp > boardtidy.txt

playertidy:
	clang-tidy-9 --header-filter='.h' --extra-arg='-std=c++17' player.cpp > playertidy.txt

randomnumbertidy:
	clang-tidy-9 --header-filter='.h' --extra-arg='-std=c++17' randomnumbergenerator.cpp > randomnumbertidy.txt

tidy: maintidy boardtidy playertidy randomnumbertidy
