#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netdb.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include "strings.h"

void error(char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char *argv[])
{
        int sockfd,newsockfd,clilen;
	char buffer[256];
        struct sockaddr_in serv_addr,cli_addr;
        int n;
        if(argc < 2)
        {
                fprintf(stderr,"Error! No port provided");
                exit(1);
        }
        
        sockfd = socket(AF_INET,SOCK_STREAM, 0);
        
        if(sockfd < 0)
        {
                error("Error opening socket");
        }
        
        bzero((char *) &serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("error on binding");
	}
	 
        listen(sockfd, 5);
        
        while(1)
        {
                clilen = sizeof(cli_addr);
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                if(newsockfd < 0)
                {
                        error("Error on accept");
                }
                
                printf("New client connection from port no. %d and IP %s \n", ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr));
                
                bzero(buffer, 256);
                n = read(newsockfd, buffer, 255);
                if(n < 0)
                {
                        error("Error reading from socket");
                }
       
	printf("Here is the message: %s\n", buffer);
	n = write(newsockfd,"I got your message", 18);
	
	if(n < 0)
	{
		error("Error writing to socket");
	}
}

}
