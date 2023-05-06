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
    int num1, num2, ans = 0, op;


    //init server & client addresses
    struct sockaddr_in serv_addr;
    portno = atoi(argv[2]);

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0){
        error("Error opening socket.");
        return -1;
    }
    /*socket, connect, write & read*/
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


    if(connect(clientfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0)
    {
        error("Failed connection");
    }
    //send operands and operators to server
    S:bzero(buffer, 255);
    n= recv(clientfd, buffer, 255, 0);
    if(n<0)
        error("ERROR reading from socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &num1);
    send(clientfd, &num1, sizeof(int), 0);   

    bzero(buffer, 255);
    n= recv(clientfd, buffer, 255, 0);
    if(n<0)
        error("ERROR reading from socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &num2);
    send(clientfd, &num2, sizeof(int), 0);    

    bzero(buffer, 255);
    n= recv(clientfd, buffer, 255, 0);
    if(n<0)
        error("ERROR reading from socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &op);
    send(clientfd, &op, sizeof(int), 0);  
    bzero(buffer, 255);  

    if(op == 5)
        goto Q;

    recv(clientfd, &ans, sizeof(int),0);
    printf("Answer is: %d\n",ans );

    if(op != 5) goto S;
    Q: printf("Exiting."); 
    shutdown(clientfd, 2);
    return 0;
}

