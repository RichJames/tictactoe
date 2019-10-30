LDFLAGS="-L/opt/lampp/lib"

testmysql: 
	g++ mysql.cpp -I/opt/lampp/include ${LDFLAGS} -lmysqlclient -Wl,--enable-new-dtags,-rpath,/opt/lampp/lib -o testmysql

clean:
	rm testmysql a.out
