#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);

    printf("Server listening on port %d...\n", PORT);

    int client_fd = accept(server_fd, NULL, NULL);
    while (1) {
        char buffer[BUFFER_SIZE] = {0};
        read(client_fd, buffer, sizeof(buffer) - 1); 
        printf("Received request:\n%s\n", buffer);

        char *response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n\r\n"
            "<html><body><h1>Hello, this is a simple web server!</h1></body></html>";

        send(client_fd, response, strlen(response), 0); 
        close(client_fd); 
    }

    close(server_fd);
    return 0;
}