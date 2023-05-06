//Karemi Ian Njaramba P15/1893/2020
//Group 8
//Iterative Connection oriented
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//function to return an error message
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
//function to write to a file
int file_write(char str[]){

   
    int count=1;
    char c;
    FILE *fptr;
    fptr = fopen("/home/hp/Documents/Networking/test.txt","a+");
    if (fptr == NULL)
    {
        printf("Error!");
        return -1 ;

    }
  
    //counts number of lines in current file and appends at the end
    for(c = getc(fptr); c!=EOF; c=getc(fptr))
        if (c== '\n')
            count= count+1;


  
    fprintf(fptr, "%d \t %s ", count, str);

    fclose(fptr);
    return 0;
}

int main(int argc, char *argv[]){
    //check if all arguments are given, otherwise throw error
    if(argc<2){

        fprintf(stderr, "\t Please input a port number.Terminating.\n");
        exit(1);
    }
    //initialize variables and message buffer
    int sockfd, newsockfd, portno, n;
    char buffer[255];
    char success[255] = "Saved.";
  
    //init server & client addresses
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;

     struct addrinfo hints, *res, *p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    //create a socket that uses TCP
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd < 0){
        error("Socket failed");
    }

    //clear any previous data from server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //get port number from CLI input
    portno = atoi(argv[1]);

    /*Assign the port number and address family IPv4 to server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //bind the socket to a port located in struct sockaddr
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding Failed");
    }
    //listen on sockfd for a maximum of 4 connections
    listen(sockfd, 4);
    cli_len = sizeof(cli_addr);

    //accept the connection and give it its own file descriptor and address information
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

    if(newsockfd < 0){
        error("Accepting error");
    }

    while (1)
    {   //clear the buffer and read client inputs
        bzero(buffer , 255);
        n = recv(newsockfd, buffer, 255,0);


        if(n <0){
             error("Error on reading");
        }else{
            //send confirm message to client and pass to file_write function
            n = send(newsockfd, success, strlen(success), 0);
            buffer[strcspn(buffer, "\n")]=0;// removes newlines
            file_write(buffer);
            
        }
        printf("Client: %s\n", buffer);//for debugging

        //read input and end
        fgets(buffer, 255, stdin);
        int i = strcmp("END", buffer);
        if(i == 0) break;
    }

    //shutdown sockets
    shutdown(newsockfd, 2);
    shutdown(sockfd,2);

    return 0;
}

