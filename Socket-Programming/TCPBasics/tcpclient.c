#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[])
{

	if(argc<2)
	{
		perror("Not Enough Arguments Provided");
		exit(1);
	}

	int network_socket;

	/* Create a Socket */
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	// Specify an Address Structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	//Connecting
	int connection_status = connect(network_socket,(struct sockaddr *)&server_address, sizeof(server_address));
	//CHECK Connection Status
	if(connection_status < 0)
	{
		perror("Could Not Connect to Server!");
		exit(1);
	}

	//RECEIVE DATA
	char buffer[1024];
	recv(network_socket, &buffer,sizeof(buffer),0);

	//Print Data Received
	printf("Message Received from Server:\n");
	printf("%s\n",buffer);

	//END CONNECTION - CLOSE SOCKET
	close(network_socket);

	return 0;
}
