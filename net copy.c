#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){

    char a[16];
    int count=1;
    char b[30];
 
    char c;
    FILE *fptr;
    fptr = fopen("/home/hp/Documents/Networking/test.txt","a+");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);

    }
    printf("Stdent Registration CLI\n");
    printf("\tEnter your name: ");
    
    fgets(b, sizeof(b), stdin);
    //puts(b);

    printf("\tEnter your registration number: ");
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")]=0;
    //scanf("%d",&a)

    for(c = getc(fptr); c!=EOF; c=getc(fptr))
        if (c== '\n')
            count= count+1;


  
    fprintf(fptr, "%d \t %s \t %s", count, a, b);
    printf("%d",count);

     fclose(fptr);

    return 0;
}

