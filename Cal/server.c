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
  char *cmd;
  struct sockaddr_in serv_addr, cli_addr;
  int  n;
  int x,y,z;

  if(argc<2)
  {
    fprintf(stderr,"error!! no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socketfd %d \n",sockfd);
  if (sockfd < 0) \
  {
    error("ERROR opening socket");
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(atoi(argv[1]));
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
  {
    error("ERROR on binding");
  }
  listen(sockfd,5);
  while(1)
  {
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    printf("newsockfd %d \n",newsockfd);	
    if (newsockfd < 0) 
    {
      error("ERROR on accept");
    }
    printf("New client connected from port no %d and IP %s \n",ntohs(cli_addr.sin_port), inet_ntoa(cli_addr.sin_addr));
    while(1)
    {
      bzero(buffer,256);
      n = read( newsockfd,buffer,255 ); 
      cmd=strtok(buffer, " :"); 
      printf("%s\n",cmd);
      if(strcmp(cmd,"add")==0)
      {
        cmd=strtok(NULL," :");
        x=atoi(cmd);
        cmd=strtok(NULL," :");
        y=atoi(cmd);
        z=x+y;
      }
      if(strcmp(buffer,"by\n")==0)
        break;
      bzero(buffer,256);
	    sprintf(buffer,"%d",z);   
	    n = write(newsockfd,buffer,strlen(buffer));
    }

  }
      
  return 0;
}
