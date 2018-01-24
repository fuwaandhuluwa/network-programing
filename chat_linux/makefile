
client:client.o sock_ntop.o
	g++ -g *.o -lpthread -o client
client.o:./src/client.cpp
	g++ -g -c ./src/client.cpp  -lpthread -o client.o
sock_ntop.o:./src/sock_ntop.cpp
	g++ -g -c ./src/sock_ntop.cpp -o sock_ntop.o
clean:
	rm -rf *.o client
