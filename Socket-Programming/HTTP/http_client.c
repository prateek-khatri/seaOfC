#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h> //IP address format conversion

int main(int argc, char *argv[])
{	
	if(argc < 3)
	{
		perror("Not enough Arguments!");
		exit(1);
	}
	char *server_address = argv[1];
	int network_socket = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(atoi(argv[2]));
	inet_aton(server_address, &remote_address.sin_addr);

	connect(network_socket,(struct sockaddr *) &remote_address,sizeof(remote_address));

	char request[] = "GET / 1.1\r\n\r\n";
	char response[4096];

	send(network_socket,request,sizeof(request),0);

	recv(network_socket,&response,sizeof(response),0);

	printf("Received from Server:");
	printf("%s\n",response);

	close(network_socket);

	return 0;
}
