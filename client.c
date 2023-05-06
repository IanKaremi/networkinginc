//Karemi Ian Njaramba P15/1893/2020
//Group 8
//Iterative Connection oriented
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
// inputs are: filename server_ip portno
int main(int argc, char *argv[]){
    //check if all arguments are given, otherwise throw error
    if(argc<3){

        fprintf(stderr, "Usage: %s HOSTNAME PORT \n", argv[0]);
        exit(1);
    }
    //initialize variables and message buffer
    int clientfd, portno, n;
    char buffer[255];

    //init server & client addresses
    struct sockaddr_in serv_addr;
    portno = atoi(argv[2]);

    //Create a TCP socket and check if functional
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0){
        error("Error opening socket.");
        return -1;
    }
    /*Assign the port number and address family IPv4 to server */
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_family = AF_INET;

      // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) 
    {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    // connect to the server or throw an error
    if(connect(clientfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0)
    {
        error("Failed connection");
    }

    printf("Please enter your name followed by registration number.\n");
    while(1)
    {   
        //clear the buffer, read input and send to server
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = send(clientfd, buffer, 255, 0);
        if (n<0) error("Error on writing");

        //receive and print text from server
        bzero(buffer, 255);
        n = recv(clientfd, buffer, 255,0);
        if(n<0) error("Error on reading");
        printf("Server: %s", buffer);

        //end the transmission
        int i = strcmp("END", buffer);
        if(i == 0) break;
    }
    //shutdown the connection
    shutdown(clientfd, 2);
    return 0;
}

