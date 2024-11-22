#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);


    connect(client_fd, (struct sockaddr*)&address, sizeof(address));

    char msg[1024] = "xyx";
    send(client_fd, msg, strlen(msg), 0);

    char res[1024] = {0};
    read(client_fd, res, sizeof(res));

    printf("%s\n", res);

    return 0;
}