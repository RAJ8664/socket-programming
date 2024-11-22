#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    address.sin_addr.s_addr = INADDR_ANY;


    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);


    int client_fd = accept(server_fd, NULL, NULL);


    FILE *file = fopen("temp.txt", "w");
    fprintf(file, "some random data is written");
    fclose(file);

    file = fopen("temp.txt", "r");
    char res[1024] = {0};
    fread(res, 1, sizeof(res), file);
    fclose(file);


    send(client_fd, res, strlen(res), 0);


    return 0;
}