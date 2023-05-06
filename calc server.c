#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[]){
    //check if all arguments are given, otherwise throw error
    if(argc<2){

        fprintf(stderr, "\t Please input a port number.Terminating.\n");
        exit(1);
    }
    //initialize variables and message buffer
    int sockfd, newsockfd, portno, n;
    char err[]= "Invalid option, terminating.";
   
  
    //init server & client addresses
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;

    
    struct addrinfo hints, *res, *p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    //argv[1] is port number
    if ((status = getaddrinfo(NULL, argv[1] , &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    //create a socket that uses TCP
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd < 0){
        error("Socket failed");
    }

    //bind the socket to a port located in struct sockaddr
    if(bind(sockfd, res->ai_addr , res->ai_addrlen) < 0){
        error("Binding Failed");
    }

    //listen on sockfd for a maximum of 4 connections
A:  listen(sockfd, 4);
    cli_len = sizeof(cli_addr);


    //accept the connection and give it its own file descriptor and address information
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

    if(newsockfd < 0){
        error("Accepting error");
    }

    int num1, num2, ans = 0, op;
    //send a request for the numbers and read them
S:  n = send(newsockfd, "Enter First integer:", strlen("Enter First integer:"),0);
    if (n<0) error("ERROR writing to socket");
    recv(newsockfd, &num1, sizeof(int), 0);
    printf("Client - First int : %d\n", num1);

    n = send(newsockfd, "Enter Second integer:", strlen("Enter Second integer:"),0);
    if (n<0) error("ERROR writing to socket");
    recv(newsockfd, &num2, sizeof(int), 0);
    printf("Client - Second int : %d\n", num2);

    n = send(newsockfd, "Choose an operation: 1.+\t 2.-\t 3.*\t 4./\t: ", strlen("Choose an operation: 1.+\t 2.-\t 3.*\t 4./\t:"),0);
    if (n<0) error("ERROR writing to socket");
    recv(newsockfd, &op, sizeof(int), 0);
    printf("Client - Operator : %d\n", op);

    switch (op)
    {
        case 1:
            ans = num1 + num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            shutdown(newsockfd, 2);
            goto A;
            break;

        case 2:
            ans = num1 - num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            shutdown(newsockfd, 2);
            goto A;
            break;

        case 3:
            ans = num1 * num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            shutdown(newsockfd, 2);
            goto A;
            break;
        case 4:
            ans = num1 / num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            shutdown(newsockfd, 2);
            goto A;
            break;        
        default:
            goto X;
            break;
    }

    if(op != 5)
        goto S;

    send(newsockfd, &ans, sizeof(int),0);

   

    
X:  printf("Error\n");
    send(newsockfd,err, sizeof(err), 0);
    
    shutdown(sockfd,2);

    return 0;
}

