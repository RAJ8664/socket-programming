//remote command execution, server.c
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
    char command[1024] = {0};
    read(client_fd, command, sizeof(command));

    char res[1024] = {0};
    FILE *fp = popen(command, "r");
    fread(res, 1, sizeof(res), fp);
    send(client_fd, res, strlen(res), 0);

    return 0;
}