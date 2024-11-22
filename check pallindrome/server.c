#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int check(char* msg, int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        if (msg[low] != msg[high]) return 0; 
        low++;
        high--;
    }
    return 1;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    int client_fd = accept(server_fd, NULL, NULL);
    
    char msg[1024] = {0};
    read(client_fd, msg, sizeof(msg));

    char* res = "";
    int x = check(msg, strlen(msg));
    if (x == 1) res = "true";
    else res = "false";

    send(client_fd, res, strlen(res), 0);

    return 0;
}