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
    }else{
        printf("Successful");
    }


    return 0;
}

