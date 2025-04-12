CC      = gcc
CFLAGS  = -O2 -Wall

all:
	$(CC) $(CFLAGS) udp_server.c -o server_udp
	$(CC) $(CFLAGS) udp_client.c -o client_udp
	$(CC) $(CFLAGS) tcp_server.c -o server_tcp
	$(CC) $(CFLAGS) tcp_client.c -o client_tcp

clean:
	-rm -f *.o *~ server_udp client_udp server_tcp client_tcp