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
   int sockfd, newsockfd,  clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;

if(argc<2)
{
fprintf(stderr,"error!! no port provided\n");
exit(1);
}
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      error("ERROR opening socket");
      //exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   //portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(atoi(argv[1]));
   //printf("SErver started");
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      error("ERROR on binding");
      //exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
//printf("SErver started");
   
   listen(sockfd,5);
while(1){
   clilen = sizeof(cli_addr);

   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (newsockfd < 0) {
      error("ERROR on accept");
      //exit(1);
   }
   printf("New client connected from port no %d and IP %s \n",ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr));
   /* If connection is established then start communicating */
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );
   
   if (n < 0) {
      error("ERROR reading from socket");
      //exit(1);
   }
   
   printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   n = write(newsockfd,"I got your message",18);
   
   if (n < 0) {
      error("ERROR writing to socket");
      //exit(1);
   }
while(1);
}
      
   return 0;
}
