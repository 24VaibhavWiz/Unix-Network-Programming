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
   int sockfd,  n;
   struct sockaddr_in serv_addr;
   //struct hostent *server;
   
   char buffer[256];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
  // portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   printf("Socket fd %d",sockfd);
   
   if (sockfd < 0) {
      error("ERROR opening socket");
      //exit(1);
   }
	
   //server = gethostbyname(argv[1]);
   
   /*if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }*/
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   //bcopy((char *)server->h_addr, (char *)&, server->h_length);
   serv_addr.sin_port = htons(atoi(argv[2]));
   serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      //exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	
   printf("Please enter the message: ");
   while(1){
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   /* Send message to the server */
   
   n = write(sockfd, buffer, strlen(buffer));   
   if(strcmp(buffer,"by\n")==0)
        break;
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);  	
   printf("%s\n",buffer);
   }


   return 0;
}
