#LDFLAGS="-L/opt/lampp/lib"
PROJ_DIR=.
COMPILER="clang++-9"
#COMPILER="g++"
DEBUG=-g
CFLAGS=-iquote$(PROJ_DIR)
GTEST_CFLAGS=`pkg-config --cflags gtest_main`
GTEST_LIBS=`pkg-config --libs gtest_main`
GMOCK_LIBS=`pkg-config --libs gmock`

testmysql: 
	${COMPILER} mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

tictactoe: main.o play_game.o randomnumbergenerator.o board.o player.o tests.o
	${COMPILER}  ${DEBUG} -o tictactoe main.o play_game.o randomnumbergenerator.o board.o player.o tests.o ${LDFLAGS} -lmysqlclient

main.o : main.cpp play_game.h input.h
	${COMPILER}  -c ${DEBUG} -o main.o main.cpp -I/opt/lampp/include -std=c++17
	
play_game.o : play_game.cpp play_game.h
	${COMPILER} -c ${DEBUG} -o play_game.o play_game.cpp -I/opt/lampp/include -std=c++17

randomnumbergenerator.o : randomnumbergenerator.cpp RandomNumberGenerator.h
	${COMPILER}  -c ${DEBUG} -o randomnumbergenerator.o randomnumbergenerator.cpp -std=c++17
	
board.o : board.cpp board.h
	${COMPILER}  -c ${DEBUG} -o board.o board.cpp -I/opt/lampp/include -std=c++17 

player.o : player.cpp player.h input.h
	${COMPILER}  -c ${DEBUG} -o player.o player.cpp -I/opt/lampp/include -std=c++17 

tests.o : tests.cpp tests.h
	${COMPILER}  -c ${DEBUG} -o tests.o tests.cpp -I/opt/lampp/include -std=c++17 

boardtests.o : tests/board_unittests.cpp 
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

playertests.o : tests/player_unittests.cpp 
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

inputtests.o : tests/input_unittests.cpp 
	${COMPILER} ${CPPFLAGS} ${CXXFLAGS} -iquote. -iquote/opt/lampp/include $< -c -o $@ ${GTEST_CFLAGS} -std=c++17

testit : inputtests.o boardtests.o playertests.o player.o board.o randomnumbergenerator.o
	${COMPILER} ${CXXFLAGS} ${LDFLAGS} $^ -v -o $@ ${GTEST_LIBS} ${GMOCK_LIBS} -lmysqlclient
	mv $@ tests/
	tests/$@

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

teststidy:
	clang-tidy-9 --header-filter='.h' --extra-arg='-std=c++17' tests.cpp > teststidy.txt

tidy: maintidy boardtidy playertidy randomnumbertidy teststidy
