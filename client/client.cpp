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
#define SRV_PORT 8000   //服务器端口
#define SRV_ADDR "192.168.1.108" //服务器ip
int main(int argc, char * argv[])
{
    const int sock_family   =  AF_INET;  //ipv4
    const int sock_type     =  SOCK_STREAM;  //tcp
    const int sock_protocol =  IPPROTO_TCP;  //tcp
    int client_sock = socket(sock_family,sock_type,sock_protocol);
    if(client_sock < 0)
    {
    	printf("创建套接字失败!n");
	exit(1);
    }
    sockaddr_in saddr;  //服务器socket addr
    socklen_t saddr_len = sizeof(saddr);
    memset(&saddr,0,saddr_len);  
    saddr.sin_family = sock_family;
    saddr.sin_port = htons(SRV_PORT);
    saddr.sin_addr.s_addr = inet_addr(SRV_ADDR);   //inet_addr在arpa/inet.h中,将字符串形式的ip地址转换为32位无符号整形.
    int srv_sock;
    while(true)
    {
    	srv_sock = connect(client_sock,(sockaddr *) &saddr,saddr_len);   //阻塞connect,直到连接成功
	if(srv_sock >= 0)
	{
	    printf("连接服务器成功!\n");
	    break;
	}
    }
    char buffer[1024];
    int i = 0;
    while(true)
    {
	while((buffer[i] = getchar()) != EOF && i < 1023)
	{
	     i++;
	}    
        write(client_sock,buffer,strlen(buffer));
	buffer[0] ='\0';
    }
    close(srv_sock);
    close(client_sock);
}

