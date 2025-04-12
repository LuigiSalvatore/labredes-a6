// =========================
// ===== SERVIDOR TCP =====
// =========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    FILE *file;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    file = fopen("recebido_tcp.txt", "w");
    int valread;
    while ((valread = read(new_socket, buffer, 1024)) > 0) {
        fwrite(buffer, sizeof(char), valread, file);
    }

    fclose(file);
    close(new_socket);
    close(server_fd);
    return 0;
}