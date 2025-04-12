// =========================
// ===== CLIENTE UDP =====
// =========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024];
    FILE *file = fopen("arquivo.txt", "r");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int n;
    while ((n = fread(buffer, sizeof(char), 1024, file)) > 0) {
        sendto(sockfd, buffer, n, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    fclose(file);
    close(sockfd);
    return 0;
}