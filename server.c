#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<poll.h>
#include<arpa/inet.h>
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr,client_addr1,client_addr2;
	int opt=1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr1,0,sizeof(client_addr1));
	memset(&client_addr2,0,sizeof(client_addr2));
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
	server_addr.sin_port=htons(8080);
	server_addr.sin_family=AF_INET;
	bind(sfd,(struct sockaddr*) &server_addr,sizeof(struct sockaddr_in));
	listen(sfd,2);
	printf("Server started running succesfully\n");
	int len1,len2;
	int nsfd1=accept(sfd,(struct sockaddr*) &client_addr1,&len1);
	int nsfd2=accept(sfd,(struct sockaddr*) &client_addr2,&len2);
	
	struct pollfd pfd[2];
	pfd[0].fd=nsfd1;
	pfd[1].fd=nsfd2;
	pfd[0].events=pfd[1].events=POLLIN;
	
	while(1)
	{
	 int r=poll(pfd,2,-1);
	 if(r<0) continue;
	 if(pfd[0].revents && POLLIN)
	 {
	 printf("Client1 is connected to the server\n");
	 char arr[20];
		recv(nsfd1,arr,20,0);
		printf("client 1 msg is:%s\n",arr);
		if(strcmp(arr,"exit\n")==0) continue;
	 }
	 
	 if(pfd[1].revents && POLLIN){
	 printf("Client2 is connected to the server\n");
	 char arr[20];
		recv(nsfd2,arr,20,0);
		printf("client 2 msg is:%s\n",arr);
		if(strcmp(arr,"exit\n")==0) continue;
	 }
	
		
	}
}

