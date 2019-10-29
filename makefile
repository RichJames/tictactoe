LDFLAGS="-L/opt/lampp/lib"

testmysql: 
	g++ mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -o testmysql

clean:
	rm testmysql a.out
