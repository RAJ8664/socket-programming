//server.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    int client_fd = accept(server_fd, NULL, NULL);

    while (1) {
        int number;
        read(client_fd, &number, sizeof(number));

        if (number % 2 == 0) {
            char* buffer = "EVEN NUMBER";
            send(client_fd, "EVEN NUMBER", strlen(buffer), 0);
        }
        else {
            char* buffer = "ODD NUMBER";
            send(client_fd, buffer , strlen(buffer), 0);
        }
    }
    return 0;
}