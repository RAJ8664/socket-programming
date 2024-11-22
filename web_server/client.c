#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr.s_addr);

    connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    char *request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(client_fd, request, strlen(request), 0);

    close(client_fd);
    return 0;
}
