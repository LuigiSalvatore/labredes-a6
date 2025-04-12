// =========================
// ===== SERVIDOR UDP ======
// =========================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv)
{
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other), recv_len;
    char buf[BUFLEN];
    FILE *outfile;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        die("socket");

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(atoi(argv[1]));
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1)
        die("bind");

    printf("Aguardando dados do cliente...\n");

    outfile = fopen("recebido_servidor.txt", "wb");
    if (!outfile) die("fopen()");

    while (1) {
        memset(buf, 0, BUFLEN);

        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *)&slen);
        if (recv_len == -1)
            die("recvfrom()");

        if (strncmp(buf, "EOF", 3) == 0) break;

        fwrite(buf, sizeof(char), recv_len, outfile);
    }

    printf("Arquivo recebido com sucesso e salvo como 'recebido_servidor.txt'!\n");
    fclose(outfile);
    close(s);
    return 0;
}
