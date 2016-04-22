#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

/*********FUNCTION PROTOTYPES*********/
void checkConnectionStatus(int connection_status);
int sendACK(int socketFD);

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
	int fileSize;
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

	connection_status = sendACK(client_socket);

	/*Receive File Size */
	char length[10];
	connection_status = recv(client_socket,length,10,0);
	checkConnectionStatus(connection_status);
	length[connection_status]= '\0';
	fileSize = atoi(length);
	printf("File Size Received: %d\n",fileSize);
	/*Send ACK for File Size */
	connection_status = sendACK(client_socket);

	/* Create File for Storing Data */
	FILE * fp = fopen(outputFileName,"wb");


	while(fileSize > 0)
	{
		bool flag = false;
		connection_status = recv(client_socket,streamBuffer,sizeof(char)*10,0);
		checkConnectionStatus(connection_status);
		printf("Chunk Received! - %d\n",connection_status);
		int i;
		for(i=0;i<connection_status;i++,fileSize--)
		{
			printf("%c",streamBuffer[i]);
		}

		fwrite(streamBuffer,connection_status,1,fp);

		printf("\n");

		if(connection_status < 10)
		{
			flag=true;
		}

		printf("Sending ACK\n");
		connection_status = send(client_socket,"ACK",3*sizeof(char),0);
		checkConnectionStatus(connection_status);
		printf("ACK Sent\n");
		if(flag)
		{
			break;
		}
	}



	/* CleanUp Code */
	fclose(fp);
	close(client_socket);
	close(network_socket);
	printf("Sucessfully Exited!\n");
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

int sendACK(int socketFD)
{
	int chk = send(socketFD,"ACK",sizeof(char)*3,0);
	checkConnectionStatus(chk);
	printf("ACK Sent!\n");
	return chk;
}
