#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr;
	int opt=1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	memset(&server_addr,0,sizeof(server_addr));
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
	server_addr.sin_port=htons(8080);
	server_addr.sin_family=AF_INET;
	//bind(sfd,(struct sockaddr*) &server_addr,sizeof(struct sockaddr_in));
	connect(sfd,(struct sockaddr*) &server_addr,sizeof(struct sockaddr_in));
	while(1)
	{
		char arr[20];
		printf("Enter any string in client2:");
		fgets(arr,20,stdin);
		send(sfd,arr,strlen(arr)+1,0);
		if(strcmp(arr,"exit\n")==0)break;
	}
	return 0;
}

