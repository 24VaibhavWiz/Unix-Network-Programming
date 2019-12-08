#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd,  n, serlen, nBytes;
	struct sockaddr_in serv_addr;
	
	char buffer[256];
	
	if(argc < 3)
	{
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	
	/* Create a socket point */
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sockfd < 0)
	{
		error("ERROR opening socket");
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	
	/* Now ask for a message from the user, this message
	* will be read by server
	*/
	serlen = sizeof(serv_addr);
	printf("Please enter the message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	nBytes = strlen(buffer) + 1;
	/* Send message to the server */
	sendto(sockfd, buffer, nBytes, 0, (struct sockaddr *) &serv_addr, serlen);
	
	if(n < 0)
	{
		error("ERROR writing to socket");
	}
	
	/* Now read server response */
	bzero(buffer, 256);
	n = recvfrom(sockfd,buffer,255,0,(struct sockaddr *) &serv_addr, &serlen);
	if(n < 0)
	{
		error("ERROR reading from socket");
	}
	printf("%s\n", buffer);
	return 0;
}
