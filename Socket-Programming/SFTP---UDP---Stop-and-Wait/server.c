#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h> 


/* GLOBAL DEFINISIONS */
#define BUFSIZE 100
#define TIMEOUT 5
bool state = false; // FALSE = PACKET 0 , TRUE = PACKET 1



/*FUNCTION PROTOTYPES */
void checkConnectionStatus(int connection_status);
bool checkTimeout(int connection_status);
void printError(char *a);
bool checkSequence(char *streamBuffer);
bool validateChecksum(char *streamBuffer);
void writeChunk(char *streamBuffer);
void sendACK();
void resendACK();



int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printError("Usage: ./server <port>");
	}

	printf("Server Started...");
	printf("Waiting for Datagrams!\n");

	/*NETWORK VARIABLS */
	int network_socket;
	int connection_status;
	struct sockaddr_in server_address;
	struct sockaddr_in clientaddr;
	struct timeval tv;
	int clientlen;
	char outputFileName[30];
	char const * const port = argv[1];
	char streamBuffer[BUFSIZE];

	//SET TIMEOUT VALUE
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	/*Create a Socket */
	network_socket = socket(AF_INET,SOCK_DGRAM,0);
	checkConnectionStatus(network_socket);

	/* FILL IN SERVER STRUCTURE */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(port));
	server_address.sin_addr.s_addr = INADDR_ANY;

	//SET SOCKET OPTIONS FOR TIMEOUT
	setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));


	/* Bind the Port */
	connection_status = bind(network_socket, (struct sockaddr*)&server_address,sizeof(server_address));
	checkConnectionStatus(connection_status);


	clientlen = sizeof(clientaddr);

	/* Here the server begins to wait for datagrams and serves them */
	while(1)
	{

		bzero(streamBuffer,BUFSIZE);
		connection_status = recvfrom(network_socket, streamBuffer,BUFSIZE,0,(struct sockaddr *) &clientaddr, &clientlen);

		if(checkTimeout(connection_status))
		{
			//This means tha the client did not recieve and ACK
			//We need to resend ACK and wait again
			printf("Timeout...resending ACK!\n");
			resendACK();
			continue;
		}

		if(!checkSequence(streamBuffer))
		{
			//The packet is out of sequence, means our ACK was not recevied
			// We need to resend old ACK and expect the next packet in sequence.
			printf("[ 1 ] Packet Received out of Sequence!\n");
			printf("[ 1 ] Resending ACK to Receive correct packet...\n");
			resendACK();
			continue;
		}
		if(!validateChecksum(streamBuffer))
		{
			//This means there is an error in the packet
			// We need to not send ACK and wait for the same packet.
			printf("[ 2 ] Checksum Error...wait for retransmission!\n");
			continue;
		}

		//Everything was checked out, we can go ahead and write the chunk to file.
		writeChunk(streamBuffer);

		//Send ACK for the packet written to file - CHANGE SEQ STATE 1 or 0
		sendACK();

	}

	return 0;
}
void writeChunk(char * streamBuffer)
{

}
bool checkSequence(char * streamBuffer)
{
	return true;
}
bool validateChecksum(char * streamBuffer)
{
	return true;
}
bool checkTimeout(int connection_status)
{
	if(connection_status <= 0)
	{
		return true;
	}
	return false;
}
void sendACK()
{
	return;
}
void resendACK()
{
	return;
}


void checkConnectionStatus(int connection_status)
{
	if(connection_status < 0)
	{
		printError("Fail to Establish Socket or Connection!\n");
	}
}

void printError(char * a)
{
	perror(a);
	exit(1);
}
