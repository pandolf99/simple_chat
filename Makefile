FLAGS = -Wall -g -std=gnu99
CLIENT = socket.o message.o sig_hand.o
SERVER = socket.o message.o

all: server client

server: server.o ${SERVER}
	gcc ${FLAGS} -o $@ $^

client: client.o ${CLIENT}
	gcc ${FLAGS} -o $@ $^

%.o : %.c
	gcc ${FLAGS} -c $< $^

server.o : server.c socket.h message.h
	gcc ${FLAGS} -c $<
client.o : client.c message.h socket.h
	gcc ${FLAGS} -c $<
message.o : message.c message.h
	gcc ${FLAGS} -c $<
socket.o : socket.c socket.h
	gcc ${FLAGS} -c $<
sig_hand.o: sig_hand.c sig_hand.h
	gcc ${FLAGS} -c $<

clean:
	rm -f server client *.o
