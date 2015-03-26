CC = clang
CFLAGS = -I/usr/local/include/ -lnanomsg -g -Werror -Wall

server: nanomsg-server.c
	${CC} nanomsg-server.c ${CFLAGS} -o bin/server

client: nanomsg-client.c
	${CC} nanomsg-client.c ${CFLAGS} -o bin/client

clean:
	rm server
	rm client

.PHONY: clean
