// =========================
// ===== CLIENTE UDP =======
// =========================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512
#define PORT 8888

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv)
{
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    FILE *infile;

    if (argc != 4) {
        printf("Usage: %s <server ip> <port> <arquivo>\n", argv[0]);
        return -1;
    }

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        die("socket");

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(atoi(argv[2]));

    if (inet_aton(argv[1], &si_other.sin_addr) == 0)
        die("inet_aton");

    infile = fopen(argv[3], "rb");
    if (!infile) die("fopen()");

    while (!feof(infile)) {
        int n = fread(buf, sizeof(char), BUFLEN, infile);
        if (sendto(s, buf, n, 0, (struct sockaddr *) &si_other, slen) == -1)
            die("sendto()");
    }

    fclose(infile);

    // Envia EOF para sinalizar fim da transmissão
    strcpy(buf, "EOF");
    sendto(s, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);

    printf("Arquivo enviado com sucesso!\n");
    close(s);
    return 0;
}
