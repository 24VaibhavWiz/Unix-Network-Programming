
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

int main( int argc, char *argv[] )
 {
   int sockfd, newsockfd,  clilen, serlen, nBytes;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[1]));  
 serv_addr.sin_addr.s_addr = INADDR_ANY;
//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	clilen = sizeof cli_addr;
	while(1){
   bzero(buffer,256);
  nBytes=recvfrom(sockfd,buffer,256,0,(struct sockaddr *) &cli_addr, &clilen); 
   printf("Here is the message: %s\n",buffer);
   
     }
      
   return 0;
}
