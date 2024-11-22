//client.c
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

    connect(client_fd, (struct sockaddr*)&address, sizeof(address));

    while (1) {
        int number;
        printf("Client Please Enter a number:\n"); scanf("%d", &number);
        send(client_fd, &number, sizeof(number), 0);

        char buffer[1024] = {0};
        read(client_fd, &buffer, 1024);
        printf("Server in Response returned :%s\n", buffer);

    }
    return 0;
}