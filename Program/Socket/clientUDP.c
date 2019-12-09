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
   //struct hostent *server;
   
   char buffer[256];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
  // portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   
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
 /*  serv_addr.sin_family = AF_INET;
   //bcopy((char *)server->h_addr, (char *)&, server->h_length);
   serv_addr.sin_port = htons(atoi(argv[2]));
serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
     memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero); */
  serv_addr.sin_family = AF_INET;
 // serv_addr.sin_port = htons(7891);
serv_addr.sin_port = htons(atoi(argv[2]));
 // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
 // memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);  
 
   
   /* Now connect to the server */
  /* if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      //exit(1);
   }*/
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
serlen=sizeof serv_addr ;	
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
       nBytes = strlen(buffer) + 1;
   /* Send message to the server */
   //n = write(sockfd, buffer, strlen(buffer));
   sendto(sockfd,buffer,nBytes,0, (struct sockaddr *) &serv_addr, serlen);
   
   if (n < 0) {
      error("ERROR writing to socket");
     // exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
  // n = read(sockfd, buffer, 255);
     // recvfrom(sockfd,buffer,255,0,(struct sockaddr *) &serv_addr, &serlen);
   if (n < 0) {
      error("ERROR reading from socket");
      //exit(1);
   }
	
   printf("%s\n",buffer);


   return 0;
}
