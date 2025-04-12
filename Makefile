# Makefile para compilar o cliente e o servidor para TCP e UDP

CC = gcc
CFLAGS = -Wall

# Definindo os arquivos de código
SOURCES_TCP = servidor_tcp.c cliente_tcp.c
SOURCES_UDP = servidor_udp.c cliente_udp.c

# Definindo os executáveis
EXEC_TCP = servidor_tcp cliente_tcp
EXEC_UDP = servidor_udp cliente_udp

# Compilação dos executáveis TCP
all: $(EXEC_TCP) $(EXEC_UDP)

$(EXEC_TCP): $(SOURCES_TCP)
	$(CC) $(CFLAGS) -o servidor_tcp servidor_tcp.c
	$(CC) $(CFLAGS) -o cliente_tcp cliente_tcp.c

$(EXEC_UDP): $(SOURCES_UDP)
	$(CC) $(CFLAGS) -o servidor_udp servidor_udp.c
	$(CC) $(CFLAGS) -o cliente_udp cliente_udp.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC_TCP) $(EXEC_UDP)
