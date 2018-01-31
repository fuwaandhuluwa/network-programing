
client1.0:client.o
	g++ -g client.o -lpthread -o client1.0
client.o:client1.0.cpp
	g++ -g -c client1.0.cpp -lpthread -o client.o
clean:
	rm -rf *.o client1.0 
