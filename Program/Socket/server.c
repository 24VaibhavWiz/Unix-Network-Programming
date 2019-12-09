#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <string.h>
#include<strings.h>
void error(char *msg)
{
perror(msg);
exit(1);
}

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd,  clilen,n;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;

if(argc<2)
{
fprintf(stderr,"error!! no port provided\n");
exit(1);
}
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   bzero((char *) &serv_addr, sizeof(serv_addr));
   //serv_addr.sin_family = AF_INET;
   //serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serv_addr.sin_port = htons(atoi(argv[1]));
   bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)); 
   listen(sockfd,5);
	while(1){
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
   printf("New client connected from port no %d and IP %s \n",ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr));
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );      
   printf("Here is the message: %s\n",buffer);
   n = write(newsockfd,"I got your message",18);   
}      
   return 0;
}
