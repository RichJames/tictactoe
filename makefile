#LDFLAGS="-L/opt/lampp/lib"
COMPILER="clang++-9"
#COMPILER="g++"
#DEBUG=-g

testmysql: 
	${COMPILER} mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

tictactoe: main.o randomnumbergenerator.o board.o player.o tests.o
	${COMPILER}  -o tictactoe main.o randomnumbergenerator.o board.o player.o tests.o ${LDFLAGS} -lmysqlclient

main.o : main.cpp board.h input.h player.h tests.h
	${COMPILER}  -c ${DEBUG} -o main.o main.cpp -I/opt/lampp/include -std=c++17

randomnumbergenerator.o : randomnumbergenerator.cpp RandomNumberGenerator.h
	${COMPILER}  -c ${DEBUG} -o randomnumbergenerator.o randomnumbergenerator.cpp -std=c++17
	
board.o : board.cpp board.h gsl-lite.hpp
	${COMPILER}  -c ${DEBUG} -o board.o board.cpp -I/opt/lampp/include -std=c++17 

player.o : player.cpp player.h input.h
	${COMPILER}  -c ${DEBUG} -o player.o player.cpp -I/opt/lampp/include -std=c++17 

tests.o : tests.cpp tests.h
	${COMPILER}  -c ${DEBUG} -o tests.o tests.cpp -I/opt/lampp/include -std=c++17 

clean:
	- rm testmysql inputtest a.out *.o *tidy.txt *.gz

realclean:
	- rm testmysql a.out *.o tictactoe

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
