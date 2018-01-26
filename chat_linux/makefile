
server:server.o sock_ntop.o
	g++ -g server.o -o server

server.o:./src/server_fork.cpp
	g++ -g -c ./src/server_fork.cpp -o server.o
sock_ntop.o:./src/sock_ntop.cpp
	g++ -g -c ./src/sock_ntop.cpp -o sock_ntop.o
clean:
	rm -rf *.o server
