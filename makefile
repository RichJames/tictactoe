#LDFLAGS="-L/opt/lampp/lib"

testmysql: 
	g++ mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

tictactoe: main.o randomnumbergenerator.o board.o
	g++ -o tictactoe main.o randomnumbergenerator.o board.o ${LDFLAGS} -lmysqlclient

main.o : main.cpp board.h input.h player.h tests.h
	g++ -c -o main.o main.cpp -I/opt/lampp/include -std=c++17

randomnumbergenerator.o : randomnumbergenerator.cpp RandomNumberGenerator.h
	g++ -c -o randomnumbergenerator.o randomnumbergenerator.cpp -std=c++17
	
board.o : board.cpp board.h
	g++ -c -o board.o board.cpp -I/opt/lampp/include -lmysqlclient -std=c++17 

clean:
	rm testmysql a.out *.o

realclean:
	rm testmysql a.out *.o tictactoe
