#LDFLAGS="-L/opt/lampp/lib"

testmysql: 
	g++ mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

tictactoe: main.o randomnumbergenerator.o board.o player.o
	g++ -o tictactoe main.o randomnumbergenerator.o board.o player.o ${LDFLAGS} -lmysqlclient

main.o : main.cpp board.h input.h player.h tests.h
	g++ -c -o main.o main.cpp -I/opt/lampp/include -std=c++17

randomnumbergenerator.o : randomnumbergenerator.cpp RandomNumberGenerator.h
	g++ -c -o randomnumbergenerator.o randomnumbergenerator.cpp -std=c++17
	
board.o : board.cpp board.h gsl-lite.hpp
	g++ -c -o board.o board.cpp -I/opt/lampp/include -lmysqlclient -std=c++17 

player.o : player.cpp player.h input.h
	g++ -c -o player.o player.cpp -I/opt/lampp/include -lmysqlclient -std=c++17 

clean:
	rm testmysql a.out *.o

realclean:
	rm testmysql a.out *.o tictactoe
