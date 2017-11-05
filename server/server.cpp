/*
 *Created by mok 2017-11-5
 *linux下用c实现socket
 *server端
 * */

#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdlib>
#define SRV_PORT 8000
#define SOCK_MAX 20

int main(int argc,char * argv[])
{
    const int sock_family = AF_INET;
    const int sock_type = SOCK_STREAM;
    const int sock_protocol = IPPROTO_TCP;
    int srv_sock = socket(sock_family,sock_type,sock_protocol);
    if(srv_sock < 0)
    {
    	printf("创建套接字失败!\n");
	exit(1);
    }
    sockaddr_in saddr;
    socklen_t srvsock_len = sizeof(saddr); 
    memset(&saddr,0,srvsock_len);
    saddr.sin_family = sock_family;
    saddr.sin_port = htons(SRV_PORT);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(srv_sock,(sockaddr *) &saddr,srvsock_len ) == -1)
    {
    	printf("端口绑定失败,请查看端口是否被占用!\n");
	exit(1);
    }
    listen(srv_sock,SOCK_MAX);
    sockaddr_in caddr;
    socklen_t clientsock_len = sizeof(caddr);
    memset(&caddr,0,clientsock_len);
    char buffer[1024];
    int client_sock;
    while(true)
    {
    	client_sock = accept(srv_sock,(sockaddr *) &caddr,&clientsock_len);
	if(client_sock >= 0)
	{
    	    printf("有客户连接进来!\n");
	    break;
	}
    }
    read(client_sock,buffer,sizeof(buffer)-1);
    printf("%s\n",buffer);
    close(srv_sock);
    close(client_sock);
    return 0;
 

}




