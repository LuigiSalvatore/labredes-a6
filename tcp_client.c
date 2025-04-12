// =========================
// ===== CLIENTE TCP =====
// =========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512

void die(const char *s) {
    perror(s);
    exit(1);
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in serv_addr;
    FILE *infile;
    char buf[BUFLEN];

    if (argc != 4) {
        printf("Usage: %s <server_ip> <port> <arquivo>\n", argv[0]);
        return -1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
        die("inet_pton");

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        die("connect");

    infile = fopen(argv[3], "rb");
    if (!infile) die("fopen");

    int bytes_read;
    while ((bytes_read = fread(buf, sizeof(char), BUFLEN, infile)) > 0) {
        if (send(sockfd, buf, bytes_read, 0) < 0)
            die("send");
    }

    printf("Arquivo enviado com sucesso via TCP!\n");
    fclose(infile);
    close(sockfd);
    return 0;
}
