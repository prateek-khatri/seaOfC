#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct frame
{
	char payload[11];
	int checksum;
	int sequenceNumber;
	int nextSeqNumber;
} frame;

int generateChecksum(char *buffer,int len)
{
	char *buf = buffer;
	int checksum = 0;
	int i;
	for(i=0;i<len;i++)
	{
		checksum += (unsigned int)(buf[i]);
	}
	return checksum;
}

void printError(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printError("Usage: <portNumber> <outputFileName>");
	}

	frame messageFrame;
	int network_socket;
	int connection_status;
	struct sockaddr_in server_address,client_address;
	int structure_length = sizeof(client_address);
	FILE *outputFile;
	char *outputFileName = argv[2];
	char * portNumber = argv[1];
	//DATA MEMBERS FOR COMPARISON
	int checksum = 0;
	char * const sendMessage = (char*)malloc(sizeof(char)*1);

	network_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(connection_status == -1)
	{
		printError("Unable to Create Socket!\n");
	}

	//CLEAR SERVER STRUCTURE
	memset((char*) &server_address,0,sizeof(server_address));

	//FILL IN THE SERVER STRUCTURE
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(portNumber));
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	//BIND SOCKET
	connection_status = bind(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
	if(connection_status == -1)
	{
		perror("Cannot Bind Port\n!");
	}

	outputFile = fopen(outputFileName,"wb");


	//START THE RECEPTION LOOP
	while(1)
	{
		printf("Waiting for Data...\n");
		connection_status = recvfrom(network_socket,&messageFrame,sizeof(messageFrame),0,(struct sockaddr *) &client_address,&structure_length);
		if(strcmp(messageFrame.payload,"exit") == 0)
		{
			printf("Data Transmission Completed...!\n");
			break;
		}

		checksum = generateChecksum(messageFrame.payload,10);
		if(checksum != messageFrame.checksum)
		{
			//WAIT FOR RETRANSMISSION AND DO NOT SEND ACK
			printf("CHECKSUM MISMATCH!!\n");
			continue;
		}

		printf("Received Data: %s\n",messageFrame.payload);
		printf("Message Verified! Writing to File...\n");
		printf("***********************\n");

		//WRITE DATA TO FILE IF CHECKSUM IS FINE
		fwrite(messageFrame.payload,sizeof(char),strlen(messageFrame.payload),outputFile);

		//SEND ACK TO CLIENT
		printf("Sending ACK for SEQ: %d\n",messageFrame.sequenceNumber);
		if(messageFrame.sequenceNumber == 0)
		{
			strcpy(sendMessage,"0");
		}
		else if(messageFrame.sequenceNumber == 1)
		{
			strcpy(sendMessage,"1");
		}
		sendto(network_socket,sendMessage,1,0,(struct sockaddr*) &client_address,structure_length);

		printf("***********************\n");
		printf("***********************\n");

		memset(messageFrame.payload,'\0',11);

	}

	//CLEANUP CODE
	close(network_socket);
	fclose(outputFile);
	free(sendMessage);

	return 0;

	


}
