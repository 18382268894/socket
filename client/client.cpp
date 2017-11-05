/*
 *Created by mok 2017-11-5
 *linux下c实现socket
 *客户端
 * */

#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#define SRV_PORT 8000
#define SRV_ADDR "192.168.1.108"
int main(int argc, char * argv[])
{
    const int sock_family   =  AF_INET;
    const int sock_type     =  SOCK_STREAM;
    const int sock_protocol =  IPPROTO_TCP;
    int client_sock = socket(sock_family,sock_type,sock_protocol);
    if(client_sock < 0)
    {
    	printf("创建套接字失败!n");
	exit(1);
    }
    sockaddr_in saddr;
    socklen_t saddr_len = sizeof(saddr);
    memset(&saddr,0,saddr_len);
    saddr.sin_family = sock_family;
    saddr.sin_port = htons(SRV_PORT);
    saddr.sin_addr.s_addr = inet_addr(SRV_ADDR);
    int srv_sock;
    while(true)
    {
    	srv_sock = connect(client_sock,(sockaddr *) &saddr,saddr_len);
	if(srv_sock >= 0)
	{
	    printf("连接服务器成功!\n");
	    break;
	}
    }
    char buffer[1024];
    std::cin>>buffer;
    write(client_sock,buffer,strlen(buffer));
    close(srv_sock);
    close(client_sock);
}

