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
	int network_socket;
	struct sockaddr_in server_address;
	int connection_status;

	network_socket = socket(AF_INET,SOCK_STREAM,0);

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	connection_status = connect(network_socket, (struct sockaddr*) &server_address,sizeof(server_address));
	checkConnectionStatus(connection_status);

	printf("Connected!\n");

	printf("Sending INIT..\n");
	char *init = "init";
	connection_status = send(network_socket,init,strlen(init)*sizeof(char),0);
	checkConnectionStatus(connection_status);

	char buff[50];
	connection_status = recv(network_socket,buff,50,0);
	checkConnectionStatus(connection_status);
	buff[connection_status] = '\0';
	printf("Received: %s\n",buff);

	printf("Sending INIT..\n");
	connection_status = send(network_socket,init,strlen(init)*sizeof(char),0);
	checkConnectionStatus(connection_status);

	connection_status = recv(network_socket,buff,50,0);
	checkConnectionStatus(connection_status);
	buff[connection_status] = '\0';
	printf("Received: %s\n",buff);


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
