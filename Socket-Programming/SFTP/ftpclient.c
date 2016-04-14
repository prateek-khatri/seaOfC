#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define SEND true
#define RECEIVE false

/*********FUNCTION PROTOTYPES*********/
void checkConnectionStatus(int connection_status);
int findLength(char const * const inputFile);
void checkACK(char tempBuffer[]);
int sendReceive(bool sendOrReceive,int socketFD,char *buffer,int size);

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
	int inputFileLength;
	char const * const port = argv[4];
	char const * const serverIP = argv[3];
	char * outputFile = argv[2];
	char const * const inputFile = argv[1];
	char * inputFileData;
	char streamBuffer[10];
	char tempBuffer[4];
	tempBuffer[3] = '\0';

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
	connection_status = sendReceive(SEND,network_socket,outputFile,strlen(outputFile));
	printf("Output File Name send Complete!\n");
	/* Wait for ACK */
	printf("Waiting for ACK..\n");
	connection_status = sendReceive(RECEIVE,network_socket,tempBuffer,3);
	printf("ACK Received for File Name!\n");
	

	/* Find Length of Input File */
	inputFileLength = findLength(inputFile);

	/* Allocate Memory for File - Easy Method*/
	inputFileData = (char*) malloc(sizeof(char)*inputFileLength);
	FILE * fp = fopen(inputFile,"r");
	fread(inputFileData,inputFileLength+1,1,fp);

	/* IF FILE IS REALLY BIG READ IT CHUNK BY CHUNK */
	/* FOR ASSIGNMENT PURPOSE ONLY SENDING WILL BE DONE CHUNK BY CHUNK */
	/* Send File in Chunks of 10 Bytes or 10 Characters */
	int i,j;
	for(i = 0;i<inputFileLength;i+=10)
	{
		for(j=i;j<10 && j<inputFileLength;j++)
		{
			//Puts 10 Bytes in Stream Buffer
			streamBuffer[j-i] = inputFileData[j];
		}
		printf("Sending Chunk %d to Server...\n",i/10);
		//Send Data To Server - Amount that was put in streamBuffer
		connection_status = sendReceive(SEND,network_socket,streamBuffer,j);
		//WAIT FOR ACK FROM SERVER
		connection_status = sendReceive(RECEIVE,network_socket,tempBuffer,3);
	}
	
	/* Left Over Chunk is Sent now */
	int remainingData = inputFileLength % 10;
	for(i= inputFileLength - remainingData,j=0;i<inputFileLength;i++,j++)
	{
		streamBuffer[j] = inputFileData[i];
	}

	printf("Sending the Last Chunk..\n");
	connection_status = sendReceive(SEND,network_socket,streamBuffer,j);

	//RECEIVE LAST ACK
	connection_status = sendReceive(RECEIVE,network_socket,tempBuffer,3);

	/* CleanUp Code */
	free(inputFileData);
	close(network_socket);

	return 0;

}
int findLength(char const * const inputFile)
{
	FILE * fp = fopen(inputFile,"r");
	fseek(fp,0,SEEK_END);
	int length = ftell(fp);
	fseek(fp,0,SEEK_SET);
	fclose(fp);
	return length;
}

void checkConnectionStatus(int connection_status)
{
	if(connection_status < 0)
	{
		perror("Fail to Establish Socket or Connection!\n");
		exit(1);
	}
}
void checkACK(char tempBuffer[])
{
	printf("%s\n",tempBuffer);
	char *cmp = "ACK";
	if(strcmp(tempBuffer,cmp) == 0)
	{
		printf("Acknowledgement Received!\n");
		//IF ACK received then clear the buffer
		tempBuffer[0] = ' ';
		tempBuffer[1] = ' ';
		tempBuffer[2] = ' ';
	}
	else
	{
		printf("ACKNOWLEDGEMENT ERROR\n");
		checkConnectionStatus(-1);
	}
}
int sendReceive(bool sendOrReceive,int socketFD,char *buffer,int size)
{
	if(sendOrReceive == true)
	{
		int chk = send(socketFD,buffer,sizeof(char)*size,0);
		checkConnectionStatus(chk);
		return chk;
	}
	else 
	{
		int chk = recv(socketFD,buffer,sizeof(char)*size,0);
		checkConnectionStatus(chk);
		checkACK(buffer);
		return chk;
	}

}
