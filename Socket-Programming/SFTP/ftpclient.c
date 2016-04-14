#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*********FUNCTION PROTOTYPES*********/
void checkConnectionStatus(int connection_status);

//Usage: <CLIENT> <input file> <output file> <server IP> <server port>
int main(int argc, char *argv[])
{
	/* Check for Command Line Arguments */
	if(argc < 5)
	{
		perror("Not Enough Arguments!\n Usage: <CLIENT> <input file> <output file> <server IP> <server port>\n");
		exit(1);
	}

	/* Network Variables */
	int network_socket;
	int connection_status;
	struct sockaddr_in server_address;
	char const * const port = argv[4];
	char const * const serverIP = argv[3];
	char const * const outputFile = argv[2];
	char const * const inputFile = argv[1];

	/* Create Network Socket */
	network_socket = socket(AF_INET,SOCK_STREAM,0);
	checkConnectionStatus(network_socket);

	/* Fill in Server Information in Structure */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(port));
	server_address.sin_addr.s_addr = inet_addr(serverIP);

	/* Try Connection to Server */
	connection_status = connect(network_socket, (struct sockaddr*) &server_address,sizeof(server_address));
	checkConnectionStatus(connection_status);
	printf("Connected to Server... \n");


	/*Send Output File Name to Server */
	printf("Sending Output File Name to Server...\n");
	connection_status = send(network_socket,outputFile,strlen(outputFile)*sizeof(char),0);
	checkConnectionStatus(connection_status);
	printf("Output File Name send Complete!\n");


	close(network_socket);

	return 0;

}

void checkConnectionStatus(int connection_status)
{
	if(connection_status < 0)
	{
		perror("Fail to Establish Socket or Connection!\n");
		exit(1);
	}
}
