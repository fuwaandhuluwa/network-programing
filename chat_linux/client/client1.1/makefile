
client1.1:client.o
	g++ -g client.o -lpthread -o client1.1
client.o:client1.1.cpp
	g++ -g -c client1.1.cpp -lpthread -o client.o
clean:
	rm -rf *.o client1.1 
