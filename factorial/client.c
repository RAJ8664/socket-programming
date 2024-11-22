//factorial client.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>


int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

    connect(client_fd, (struct sockaddr*)&address, sizeof(address));

    int number;
    printf("Enter a number:\n"); scanf("%d", &number);
    send(client_fd, &number, sizeof(number), 0);

    int res;
    read(client_fd, &res, sizeof(res));
    printf("The factorial of Number is :%d\n", res);
    return 0;
}