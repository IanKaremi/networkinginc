#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
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

    //create a socket that uses TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Socket failed");
    }

    //clear any previous data from server address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //get port number from CLI input
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding Failed");
    }

    listen(sockfd, 4);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

    if(newsockfd < 0){
        error("Accepting error");
    }

    while (1)
    {
        bzero(buffer , 255);
        n = recv(newsockfd, buffer, 255,0);
        if(n <0){
             error("Error on reading");
        }else{
            n = send(newsockfd, success, strlen(success), 0);
            buffer[strcspn(buffer, "\n")]=0;
            file_write(buffer);
            
        }
        printf("Client: %s\n", buffer);
        fgets(buffer, 255, stdin);
    
        

        int i = strcmp("END", buffer);
        if(i == 0) break;
    }

    
    shutdown(newsockfd, 2);
    shutdown(sockfd,2);

    return 0;
}

