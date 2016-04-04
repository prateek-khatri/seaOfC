#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		perror("Not Enough Arguments");
		exit(1);
	}

	char message[1024] = "You have connected to the server bro!";
	int server_socket;

	//CREATE SOCKET
	server_socket = socket(AF_INET, SOCK_STREAM,0);

	//define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;


	//BIND THE SOCKET
	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	//LISTEN FOR CONNECTIONS
	listen(server_socket,2);  // - second argument for backlog

	//ACCEPT CONNECTION
	int client_socket;
	client_socket = accept(server_socket,NULL,NULL);  //- 2nd arguement is to identify where the client is connecting from

	//SEND DATA
	send(client_socket,message,sizeof(message),0);
	listen(server_socket,2);
	//CLOSE SOCKET CONNECTIONS
	close(server_socket);
	return 0;
}
