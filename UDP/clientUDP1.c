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

int main(int argc, char *argv[]) {
   int sockfd,  n, serlen, nBytes;
   struct sockaddr_in serv_addr;   
   char buffer[256];
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
   bzero((char *) &serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[2]));
 // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

   serlen=sizeof serv_addr ;	
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
       nBytes = strlen(buffer) + 1;
   sendto(sockfd,buffer,nBytes,0, (struct sockaddr *) &serv_addr, serlen);

   bzero(buffer,256);
     // recvfrom(sockfd,buffer,255,0,(struct sockaddr *) &serv_addr, &serlen);
   printf("%s\n",buffer);

   return 0;
}
