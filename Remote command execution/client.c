//remote command execution, client.c
#include<stdio.h>
#include<stdlib.h>
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

    char command[1024] = "ls";
    send(client_fd, command, strlen(command), 0);

    char res[1024] = {0};
    read(client_fd, res, sizeof(res));
    printf("%s", res);
    
    return 0;
}