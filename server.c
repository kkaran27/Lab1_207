#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7820

int main() {
    int file_descriptor_server, new_socket;
    struct sockaddr_in server_address;
    int address_length = sizeof(server_address);

    int x;

    file_descriptor_server = socket(AF_INET, SOCK_STREAM, 0);
    if(file_descriptor_server < 0) {
        perror("Cannot create a socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    if(bind(file_descriptor_server, (struct sockaddr*)&server_address,address_length) < 0 ) {
        perror("Cannot bind to port");
        exit(EXIT_FAILURE);
    }

    if(listen(file_descriptor_server, 10) < 0) {
        perror("Queue may be full");
        exit(EXIT_FAILURE);
    }

    new_socket = accept(file_descriptor_server, (struct sockaddr*)&server_address, (socklen_t*)&address_length);

    if(new_socket < 0) {
        perror("Cannot accept connection");
        exit(EXIT_FAILURE);
    }

    read(new_socket, &x, sizeof(int));
    printf("The integer received from the client is %d\n", x);
    x--;
    write(new_socket,&x, sizeof(int));
    return 0;
}
