// =========================
// ===== SERVIDOR UDP =====
// =========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[1024];
    FILE *file = fopen("recebido_udp.txt", "w");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    int n;
    while ((n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&cliaddr, &len)) > 0) {
        fwrite(buffer, sizeof(char), n, file);
        if (n < 1024) break; // fim de arquivo
    }

    fclose(file);
    close(sockfd);
    return 0;
}