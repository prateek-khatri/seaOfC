#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*********FUNCTION PROTOTYPES*********/
void checkConnectionStatus(int connection_status);

//Usage: <SERVER> <port>
int main(int argc, char *argv[])
{
	/* Check for Command Line Arguments */
	if(argc<2)
	{
		perror("Not Enough Arguments!\n Usage: <SERVER> <port>\n");
		exit(1);
	}

	/* Network Variables */
	int network_socket, client_socket;
	int connection_status;
	struct sockaddr_in server_address;
	char outputFileName[30];
	char const * const port = argv[1];
	char streamBuffer[10];
	char fileBuffer[5];

	/* Create a Socket */
	network_socket = socket(AF_INET,SOCK_STREAM,0);
	checkConnectionStatus(network_socket);

	/* Fill in Server Structure */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(port));
	server_address.sin_addr.s_addr = INADDR_ANY;

	
	/* Bind Port to Socket - Listen  */
	bind(network_socket, (struct sockaddr*)&server_address,sizeof(server_address));
	printf("Waiting for Connection...\n");
	listen(network_socket,2);
	

	/* Accept Incoming Connection */
	client_socket = accept(network_socket,NULL,NULL);

	/* Receive First Data Segment - Output File Name */
	connection_status = recv(client_socket,outputFileName,30,0);
	checkConnectionStatus(connection_status);
	outputFileName[connection_status] = '\0';
	printf("Output File Name Received: %s\n",outputFileName);

	connection_status = send(client_socket,"ACK",3*sizeof(char),0);
	checkConnectionStatus(connection_status);
	printf("ACK Sent\n");
	/* Create File for Storing Data */
	FILE * fp = fopen(outputFileName,"w");
	sleep(1);

	while(1)
	{

		connection_status = recv(client_socket,streamBuffer,sizeof(char)*10,0);
		checkConnectionStatus(connection_status);
		printf("Chunk Received!\n");

		fwrite(streamBuffer,11,1,fp);
		printf("%s\n",streamBuffer);


		printf("Sending ACK\n");
		connection_status = send(client_socket,"ACK",3*sizeof(char),0);
		checkConnectionStatus(connection_status);
		printf("ACK Sent\n");
	}



	/* CleanUp Code */
	fclose(fp);
	close(client_socket);
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
