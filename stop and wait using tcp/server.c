//server.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int count;
int main() {
    count = 0;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    int client_fd = accept(server_fd, NULL, NULL);

    char toreceive[1024] = {0};
    char tosend[1024] = {0};
    while (1) {
        read(client_fd, toreceive, sizeof(toreceive));
        printf("Frame received:%s\n", toreceive);
        if (count % 4 == 0) {
            printf("Incorrect ack :Resend the frame:\n");
            printf("Frame resent:%s\n", toreceive);
        }
        strcpy(tosend, toreceive);
        send(client_fd, tosend, strlen(tosend), 0);
        printf("correct ack send\n");
        count++;
    }
    return 0;
}
