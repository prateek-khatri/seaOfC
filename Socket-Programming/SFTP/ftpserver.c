#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{

	if(argc<2)
	{
		perror("Not Enough Arguments! Usage:<ftpserver> PORT_NUM\n");
		exit(1);
	}
	/* NETWORK VARIABLES */
	int network_socket,client_socket;
	int connection_status;
	struct sockaddr_in server_address;
	char const * const server_port = argv[1];
	char buffer[5];
	char fileName[30];
	char temp = ' ';

	/* Fill Address Structure */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(server_port));
	server_address.sin_addr.s_addr = INADDR_ANY;

	/* CREATE SOCKET */
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	/* BIND SOCKET - ACCEPT CONNECTION */
	bind(network_socket, (struct sockaddr*)&server_address,sizeof(server_address));
	listen(network_socket,5);
	printf("Waiting for Connection...\n");
	client_socket = accept(network_socket,NULL,NULL);

	recv(network_socket,&fileName,sizeof(char)*30,0);
	
	connection_status = send(network_socket,"OK",sizeof(char)*2,0);

	printf("Filname Received: %s\n",fileName);

	/* CREATE FILE IN APPEND MODE */
	FILE *output = fopen(fileName,"a");

	/*Start Reading Data */
	while(recv(network_socket,&temp,sizeof(char), MSG_PEEK | MSG_DONTWAIT) != 0)
	{
		recv(network_socket,&buffer,sizeof(char)*5,0);
		printf("%s",buffer);
		fwrite(buffer,sizeof(char),sizeof(char)*5,output);

	}
	fclose(output);
	close(network_socket);

	return 0;
}
