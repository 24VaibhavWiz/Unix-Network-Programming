#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, clilen, serlen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    if(argc < 2)
    {
        fprintf(stderr, "error!! no port provided\n");
        exit(1);
    }

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        error("ERROR opening socket");
    }

    /* Initialize socket structure */
    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    /* Now bind the host address using bind() call.*/
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }

    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */

    clilen = sizeof(cli_addr);
    while(1)
    {
        if(newsockfd < 0)
        {
            error("ERROR on accept");
        }
        //printf("New client connected from port no %d and IP %s \n",ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr));
        /* If connection is established then start communicating */
        bzero(buffer, 256);
        
        n = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *) &cli_addr, &clilen);

        printf("Here is the message: %s\n", buffer);

        n = sendto(sockfd,buffer,255,0, (struct sockaddr *) &cli_addr, clilen);
        if(n < 0)
        {
            error("ERROR writing to socket");
        }
    }

    return 0;
}
