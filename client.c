//
// Created by karan on 9/23/17.
//
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 7820

int main() {
    struct sockaddr_in server_address;
    int sock = 0;
    int value = 6;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        printf("Check the address\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Cannot connect to the server \n");
        return -1;
    }

    write(sock, &value, sizeof(int));
    read(sock, &value, sizeof(int));
    printf("The integer received back from the server is %d\n", value);

    return 0;
}