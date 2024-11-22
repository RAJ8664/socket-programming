//client.c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

    connect(client_fd, (struct sockaddr*)&address, sizeof(address));
    
    char tosend[1024] = {0};
    char toreceive[1024] = {0};
    int frame = 15;
    while (frame > 0) {
        frame--;
        printf("Enter a frame to send:\n");
        clock_t t = clock();
        fgets(tosend, sizeof(tosend), stdin);
        t = clock() - t;
        double time_take =  ((double)(t)/ CLOCKS_PER_SEC);
        if (time_take > (double)(0.0009)) {
            printf("Time out: Resending the Frame:%s\n", tosend);
        }

        send(client_fd, tosend, strlen(tosend), 0);
        printf("message Sent: %s\n", tosend);

        read(client_fd, toreceive, sizeof(toreceive));
        if (strcmp(tosend, toreceive) == 0) {
            printf("correct ack received\n");
            frame--;
        }
        else {
            printf("Incorrect ack recending the frame %d\n", frame);
        }
    }
    return 0;
}