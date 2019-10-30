LDFLAGS="-L/opt/lampp/lib"

testmysql: 
	g++ mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

tictactoe: main.o randomnumbergenerator.o
	g++ -o tictactoe main.o randomnumbergenerator.o

main.o : main.cpp
	g++ -c -o main.o main.cpp -std=c++17

randomnumbergenerator : randomnumbergenerator.cpp
	g++ -c -o randomnumbergenerator.o randomnumbergenerator.cpp -std=c++17
	
clean:
	rm testmysql a.out *.o

realclean:
	rm testmysql a.out *.o tictactoe
