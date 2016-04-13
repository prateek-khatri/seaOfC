#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*********FUNCTION PROTOTYPES*********/
void checkConnectionStatus(int connection_status);


int main(int argc, char *argv[])
{
	int network_socket,client_socket;
	struct sockaddr_in server_address;
	int connection_status;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;

	network_socket = socket(AF_INET,SOCK_STREAM,0);

	bind(network_socket, (struct sockaddr*)&server_address,sizeof(server_address));
	listen(network_socket,2);
	printf("Waiting for Connection..\n");

	client_socket = accept(network_socket,NULL,NULL);

	char buf[50];
	connection_status = recv(client_socket,buf,50,0);
	checkConnectionStatus(connection_status);
	buf[connection_status] = '\0';
	printf("Recv: %s\n",buf);

	char *received = "received";
	connection_status = send(client_socket,received, sizeof(char)*strlen(received),0);
	checkConnectionStatus(connection_status);
	printf("Received Sent...\n");

	connection_status = recv(client_socket,buf,50,0);
	checkConnectionStatus(connection_status);
	buf[connection_status] = '\0';
	printf("Recv: %s\n",buf);

	connection_status = send(client_socket,received, sizeof(char)*strlen(received),0);
	checkConnectionStatus(connection_status);
	printf("Received Sent...\n");

	close(client_socket);
	close(network_socket);
	return 0;

}
void checkConnectionStatus(int connection_status)
{
	if(connection_status < 0)
	{
		perror("Fail to Send/Receive Message to/from Server!\n");
		exit(1);
	}
}
