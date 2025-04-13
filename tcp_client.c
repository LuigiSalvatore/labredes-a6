/* 
    TCP client para enviar um arquivo para o servidor
    uso: ./tcpclient <hostname> <porta> <arquivo>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

void die(char *s) {
    perror(s);
    exit(1);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    FILE *file;

    if (argc != 4) {
        fprintf(stderr,"uso: %s <hostname> <porta> <arquivo>\n", argv[0]);
        exit(0);
    }

    hostname = argv[1];
    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        die("socket");

    server = gethostbyname(hostname);
    if (server == NULL)
        die("gethostbyname");

    memset((char *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);

    if (inet_aton(hostname, &serveraddr.sin_addr) == 0)
        die("inet_aton");

    printf("Tentando conectar em %s:%d...\n", hostname, portno);
    if (connect(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) 
        die("connect");

    // Abre o arquivo que será enviado
    file = fopen(argv[3], "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        close(sockfd);
        exit(1);
    }

    // Envia o conteúdo do arquivo em blocos
    while (!feof(file)) {
        memset(buf, 0, BUFSIZE);
        size_t bytes_read = fread(buf, 1, BUFSIZE, file);
        if (bytes_read > 0) {
            n = write(sockfd, buf, bytes_read);
            if (n < 0) die("write");
        }
    }

    printf("Arquivo enviado com sucesso.\n");

    fclose(file);
    close(sockfd);
    return 0;
}
