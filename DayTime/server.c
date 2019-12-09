/*Socket :  Server*/
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
 #include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char **argv)
{
  int listenfd,connfd,len,ib,n;
  struct sockaddr_in servaddr,clientaddr;
  char buff[1024];
  len=sizeof(struct sockaddr_in);
  listenfd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(0);
  bind(listenfd,(struct sockaddr *)&servaddr, sizeof(servaddr));
  getsockname(listenfd, (struct sockaddr *)&servaddr, &len);
  printf("After bind ephemeral port=%d\n",(int)ntohs (servaddr.sin_port));
  listen(listenfd,5);
  connfd=accept(listenfd, (struct sockaddr *)&clientaddr,&len);
  write(connfd,"UNP st",7);
  close(connfd);
}
