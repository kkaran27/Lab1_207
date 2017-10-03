//*********************************************************************************************
//Header files.                                                                               *
//*********************************************************************************************
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//*********************************************************************************************
//Defining Port number as constant                                                            *
//*********************************************************************************************
#define PORT 7820

//*********************************************************************************************
//Main Function                                                                               *
//*********************************************************************************************
int main() {

    int file_descriptor_server, new_socket;
    struct sockaddr_in server_address;
    int address_length = sizeof(server_address);

    int x;

    //Creating socket by calling socket function.
    file_descriptor_server = socket(AF_INET, SOCK_STREAM, 0);

    //Check whether the socket is created or not. If it is not created then display error message.
    if(file_descriptor_server < 0) {
        perror("Cannot create a socket");
        exit(EXIT_FAILURE);
    }

    //Assigning the address family, port number and server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    //Check whether the socket is bind to the server address. It it is not binded to it then display error message
    if(bind(file_descriptor_server, (struct sockaddr*)&server_address,address_length) < 0 ) {
        perror("Cannot bind to port");
        exit(EXIT_FAILURE);
    }

    //Listen for incoming requests on the listening socket, and display an error message if the listening queue becomes full.
    if(listen(file_descriptor_server, 10) < 0) {
        perror("Queue may be full");
        exit(EXIT_FAILURE);
    }

    //Accepting a client's connection request and creating a new connected socket to handle the interaction with the client.
    new_socket = accept(file_descriptor_server, (struct sockaddr*)&server_address, (socklen_t*)&address_length);

    //Check whether the client's connection request was accepted, if it was not accepted then display an error message.
    if(new_socket < 0) {
        perror("Cannot accept connection");
        exit(EXIT_FAILURE);
    }

    //read client's data from connected socket.
    read(new_socket, &x, sizeof(int));

    //Display the data client has sent.
    printf("The integer received from the client is %d\n", x);

    x--;

    //write data back to connected socket
    write(new_socket,&x, sizeof(int));

    return 0;
}
