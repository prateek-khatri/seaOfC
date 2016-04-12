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
	if(argc<5)
	{
		perror("Not Enough Arguments! Usage: INPUT_FILE OUTPUT_FILE IP_ADDDRESS PORT_NUM\n");
		exit(1);
	}

	/* Network Variables */
	int network_socket;
	struct sockaddr_in server_address;
	int connection_status;
	int input_file_length;
	char const * const input_file = argv[1];
	char const * const output_file = argv[2];
	char const * const server_ip = argv[3];
	char const * const server_port = argv[4];
	char buffer[10];


	/* CREATE SOCKET */
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	/* FILL ADDRESS STRUCTURE*/
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(server_port));
	server_address.sin_addr.s_addr = inet_addr(server_ip);

	/* START CONNECTION */
	connection_status = connect(network_socket, (struct sockaddr*) &server_address,sizeof(server_address));
	checkConnectionStatus(connection_status);

	/* SEND OUTPUT FILE NAME TO SERVER */
	printf("Sending Output File Name to the Server...\n");
	connection_status = send(network_socket,&output_file,sizeof(char)*strlen(output_file),0);
	checkConnectionStatus(connection_status);

	/*Send End of File Name to Server */
	connection_status = send(network_socket,"^",sizeof(char),0);
	checkConnectionStatus(connection_status);

	char ok[2];
	while(ok[0] != 'O' && ok[1] != 'K')
	{
		recv(network_socket,&ok,sizeof(char)*2,0);
	}
	printf("%s\n",ok);
	exit(0);
	/* Start Reading Input File */
	FILE *input = fopen(input_file,"r");
	if(input == NULL)
	{
		printf("Unable to open File <%s>\n",input_file);
		exit(1);
	}

	/*FINE Length of File */
	fseek(input,0,SEEK_END);
	input_file_length = ftell(input);
	fseek(input,0,SEEK_SET);
	
	/* Read 10 bytes at a time and send to server */
	printf("Sending File to Server...\n");
	while(!feof(input))
	{
		fread(buffer,sizeof(char),10,input);
		if(ferror(input))      
		{
        	perror("Unable to Read File!");
        	exit(1);
      	}
      	connection_status = send(network_socket,buffer,sizeof(char)*10,0);
		checkConnectionStatus(connection_status);
	}
	printf("Closing Network Socket...\n");
	close(network_socket);
	fclose(input);
	return 0;
}

void checkConnectionStatus(int connection_status)
{
	if(connection_status < 0)
	{
		perror("Fail to Send Message to Server!\n");
		exit(1);
	}
}
