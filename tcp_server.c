/*
    Servidor TCP para receber um arquivo e salvar como 'recebido.txt'
    Uso: ./servidor_tcp <porta>
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 1024

void die(char *s) {
    perror(s);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, connfd, port, recv_len;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buf[BUFLEN];

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <porta>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    // Cria socket TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket");

    // Prepara estrutura do servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // Faz o bind
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        die("bind");

    // Escuta conexões
    if (listen(sockfd, 5) < 0)
        die("listen");

    printf("Servidor escutando na porta %d...\n", port);

    clilen = sizeof(cli_addr);

    while (1) {
        printf("Aguardando conexão de cliente...\n");

        // Aceita conexão do cliente
        connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (connfd < 0)
            die("accept");

        printf("Cliente conectado: %s:%d\n",
               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        // Abre arquivo para escrita
        FILE *file = fopen("recebido.txt", "wb");
        if (!file) {
            perror("Erro ao criar o arquivo");
            close(connfd);
            continue;
        }

        // Recebe dados e grava no arquivo
        while ((recv_len = read(connfd, buf, BUFLEN)) > 0) {
            fwrite(buf, 1, recv_len, file);
        }

        printf("Arquivo recebido e salvo como 'recebido.txt'\n");

        fclose(file);
        close(connfd);
    }

    close(sockfd);
    return 0;
}
