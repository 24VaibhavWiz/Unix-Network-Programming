/*Socket : :DAY Time Client*/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char *argv[])
{
int sockfd,n,conn;
char recvline[1024];
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(atoi(argv[1]));
conn=connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 n=read(sockfd,recvline,1024);
 printf("Number of bytes received from server::%d\n",n);
 recvline[n]=0;
 printf("Msg from server:::%s\n",recvline);
 exit(0);

}
