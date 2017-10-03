//*********************************************************************************************
//Header files.                                                                               *
//*********************************************************************************************
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

//*********************************************************************************************
//Defining Port number as constant                                                            *
//*********************************************************************************************
#define PORT 7820

//*********************************************************************************************
//Main Function                                                                               *
//*********************************************************************************************
int main() {

    struct sockaddr_in server_address;
    int sock = 0;
    int value = 6;

    //Creating socket by calling socket function.
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //Check whether the socket is created or not. If it is not created then display error message.
    if(sock < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    //Setting the server address value to 0's
    memset(&server_address, 0, sizeof(server_address));

    //Assigning Port number and address family to the socket.
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;

    //Check whether the server address is valid or not. If it is invalid then display the error message.
    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        printf("Check the address\n");
        return -1;
    }

    //Check whethe the socket is connected to the server or not. If it is not connected then display the error message.
    if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Cannot connect to the server \n");
        return -1;
    }

    //send data to socket
    write(sock, &value, sizeof(int));

    //read data from socket
    read(sock, &value, sizeof(int));

    //Display the integer received from server.
    printf("The integer received back from the server is %d\n", value);

    return 0;
}