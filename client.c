//client.c
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);
    
    connect(client_fd, (struct sockaddr*)&address, sizeof(address));
    
    char buffer[1024] = {0};
    read(client_fd, buffer, 1024);
    printf("message from server:%s\n", buffer);
    return 0;
}