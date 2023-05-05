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

    int num1, num2, ans = 0, op;

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
            break;

        case 2:
            ans = num1 - num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            break;

        case 3:
            ans = num1 * num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            break;
        case 4:
            ans = num1 / num2;
            printf("ANS: %d\n",ans);
            send(newsockfd, &ans, sizeof(int),0);
            break;        
        default:
            goto X;
            break;
    }

    if(op != 5)
        goto S;

    send(newsockfd, &ans, sizeof(int),0);

   

    
X:  printf("Error\n");
    shutdown(newsockfd, 2);
    shutdown(sockfd,2);

    return 0;
}

