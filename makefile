client-server: client server

client: client.o tands.o
	gcc -o client client.o tands.o

client.o: client.c client.h tands.c tands.h
	gcc -c client.c tands.c

server: server.o tands.o
	gcc -o server server.o tands.o

server.o: server.c server.h tands.c tands.h
	gcc -c server.c tands.c

tands.o: tands.c tands.h
	gcc -c tands.c

clean:
	rm -rf *.o *.log server client