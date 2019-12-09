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
int main(int argc, char *argv[]) {
   int sockfd,  n;
   struct sockaddr_in serv_addr;
   char buffer[256];
   sockfd = socket(AF_INET, SOCK_STREAM, 0);   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(atoi(argv[2]));
   serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
   connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = write(sockfd, buffer, strlen(buffer));   
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);	
   printf("%s\n",buffer);
   return 0;
}
