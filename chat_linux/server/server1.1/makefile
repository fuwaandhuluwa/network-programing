
server1.1:server.o sock_ntop.o str_echo.o sock_rw.o
	g++ -g *.o -o server1.1

server.o:../../src/server.cpp
	g++ -g -c ../../src/server.cpp -o server.o
sock_ntop.o:../../src/sock_ntop.cpp
	g++ -g -c ../../src/sock_ntop.cpp -o sock_ntop.o

str_echo.o:../../src/str_echo.cpp
	g++ -g -c ../../src/str_echo.cpp -o str_echo.o
sock_rw.o:../../src/sock_rw.cpp
	g++ -g -c ../../src/sock_rw.cpp -o sock_rw.o

clean:
	rm -rf *.o server1.1
