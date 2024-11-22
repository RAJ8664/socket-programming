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

    char* msg[] = {"frame1, frame2, frame3"};



    char toreceive[1024] = {0};
    char tosend[1024] = {0};
    for (int i = 0; i < 3; i++) {
        printf("Sending Frame:%s\n", msg[i]);
        send(client_fd, msg[i], sizeof(msg[i]), 0);
        printf("Frame Sent:%s\n", msg[i]);

        read(client_fd, toreceive, strlen(toreceive));
        printf("Frame ack:%s\n", toreceive);
    }


    return 0;
}