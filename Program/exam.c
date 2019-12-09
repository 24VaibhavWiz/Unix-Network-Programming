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
int main()
{
	int x=ntohs(256);
	printf("%d \n",x);
	struct sockaddr_in c;
	//int y=inet_aton("12.12.12.12",(struct in_addr *)&c);
	c.sin_addr.s_addr=inet_addr("0.0.1.0");

	printf("%d\n",c.sin_addr.s_addr);

	struct in_addr aton;
	inet_aton("0.0.1.0",&aton);
	printf("%d\n",aton.s_addr);

	struct in_addr ntoa;
	ntoa.s_addr=65536;
	char *rn=inet_ntoa(ntoa);
	printf("%s\n",rn);

    struct in_addr pton;
    inet_pton(AF_INET,"0.0.1.0",&pton);
    printf("%d\n",pton.s_addr);

    char str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &pton, str, INET_ADDRSTRLEN);

    printf("%s\n",str );
     




}