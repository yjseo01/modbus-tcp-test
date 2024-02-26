CC = gcc
CFLAGS = -Wall

all: Client Server

Client: Client.o ClientFunc.o
	$(CC) $(CFLAGS) -o Client Client.o ClientFunc.o -lmodbus

Client.o: Client.c
	$(CC) $(CFLAGS) -c -o Client.o Client.c
ClientFunc.o: ClientFunc.c
	$(CC) $(CFLAGS) -c -o ClientFunc.o ClientFunc.c

Server: Server.o ServerFunc.o
	$(CC) $(CFLAGS) -o Server Server.o ServerFunc.o -lmodbus

Server.o: Server.c
	$(CC) $(CFLAGS) -c -o Server.o Server.c

ServerFunc.o: ServerFunc.c
	$(CC) $(CFLAGS) -c -o ServerFunc.o ServerFunc.c

clean:
	rm -f *.o Client Server
