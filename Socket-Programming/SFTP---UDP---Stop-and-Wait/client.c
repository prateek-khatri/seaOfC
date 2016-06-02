#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

int findLength(char const * const inputFile)
{
    FILE * fp = fopen(inputFile,"rb");
    fseek(fp,0,SEEK_END);
    int length = ftell(fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    return length;
}

typedef struct frame
{
	char payLoad[11];
	int checksum;
	int sequenceNumber;
	int nextSeqNumber;
} frame;


void printError(char *msg)
{
	perror(msg);
	exit(1);
}

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

int main(int argc,char *argv[])
{
	if(argc < 5)
	{
		perror("Not Enough Arguments!\n Usage: <CLIENT> <input file> <output file> <server IP> <server port>\n");
		exit(1);
	}
	/* Network Variables */
	frame messageFrame;
	int counter;
	int network_socket;
	int connection_status;
	int checksum = 0;
	struct sockaddr_in server_address;
	int structure_lenght = sizeof(server_address);
	struct timeval tv;
	char const * const port = argv[4];
	char const * const serverIP = argv[3];
	char const * const outputFile = argv[2];
	char const * const inputFile = argv[1];
	char * const inputFileData= (char*)malloc(sizeof(char)*11);
	char * const tempBuffer =(char*)malloc(sizeof(char)*5);
	FILE *file_pointer;
    file_pointer = fopen(inputFile,"rb");

	/* CREATE UDP SOCKET */
	network_socket =socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(network_socket == -1)
	{
        printError("Unable to Create Socket!\n");
    }

    /* ZERO THE STRUCTURE */
    memset((char*) & server_address,0,sizeof(server_address));
    
    /* Fill in Socket Structure */
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(port));

    connection_status = inet_aton(serverIP , &server_address.sin_addr);
    if (connection_status == 0) 
    {
        printError("inet_aton() failed\n");
    }

    /* Set Timeout */	
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    /* Set socket option to timeout on recvfrom */
    setsockopt(network_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

    //Initialize Counter
    counter =0;

    int n;


    //INITIATLIZE FOR FIRST PACKET - Toggles in loop
    messageFrame.sequenceNumber = 1;
    messageFrame.nextSeqNumber = 0;

    //DO ALL THE SHIZZLE WIZZLE HERE
    while((n=fread(inputFileData,1,10,file_pointer)) > 0)
    {
        memset(messageFrame.payLoad,'\0',11);
    	memset(tempBuffer,'\0',5);
    	strncpy(messageFrame.payLoad,inputFileData,n);
    	checksum = generateChecksum(inputFileData,sizeof(inputFileData));
    	messageFrame.checksum = checksum;

    	//TOGGLE THE SEQUENCES FOR SENDING
    	if(messageFrame.sequenceNumber == 1)
    	{
    		messageFrame.sequenceNumber = 0;
    		messageFrame.nextSeqNumber = 1;
    	}
    	else if(messageFrame.sequenceNumber == 0)
    	{
    		messageFrame.sequenceNumber = 1;
    		messageFrame.nextSeqNumber = 0;
    	}

RESEND:
    	printf("Sending Packet Seq: %d to server...........%d\n",messageFrame.sequenceNumber,counter);
        printf("DATA: %s, %d\n",messageFrame.payLoad,checksum);
    	sendto(network_socket,&messageFrame,sizeof(messageFrame),0,(struct sockaddr*) &server_address,sizeof(server_address));
        counter++;

    	int received_bytes = recvfrom(network_socket,tempBuffer,1,0,(struct sockaddr*) &server_address,&structure_lenght);
    	if(strcmp(tempBuffer,"0") == 0 && messageFrame.sequenceNumber== 0)
    	{
    		printf("RECEIVED: ACK 0\n\n");
    	}
    	else if(strcmp(tempBuffer,"1") == 0 && messageFrame.sequenceNumber== 1)
    	{
    		printf("RECEIVED: ACK 1\n\n");
    	}
    	else //TIMEOUT or WRONG SEQUENCE
    	{
    		goto RESEND;
    	}
        if(n<10) break;


    }

    messageFrame.payLoad[0] = 'e';
    messageFrame.payLoad[1] = 'x';
    messageFrame.payLoad[2] = 'i';
    messageFrame.payLoad[3] = 't';
    messageFrame.payLoad[4] = '\0';
    sendto(network_socket,&messageFrame,sizeof(messageFrame),0,(struct sockaddr*) &server_address,sizeof(server_address));
    free(inputFileData);
    free(tempBuffer);
    close(network_socket);

}
