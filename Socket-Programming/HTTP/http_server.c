#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#define SIZEOUT(A) #A
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		perror("Not Enough Arguments! Usage: PORT");
		exit(1);
	}
	//OPEN HTML FILE
	FILE *html_data = fopen("index.html","r");
	if(html_data == NULL)
	{
		perror("Cannot Open File!");
		exit(1);	
	}
	//PUT FILE IN MEMORY
	char * header = "HTTP/1.1 200 OK\n\n";
	fseek(html_data,0,SEEK_END);
	int length = ftell(html_data);
	fseek(html_data,0,SEEK_SET);
	char *buffer = (char *)malloc(sizeof(char)*(length+strlen(header)));
	int  i=0;
	char c;
	
	while(i<strlen(header))
	{
		buffer[i] = header[i++];
	}
	while((c = fgetc(html_data)) != EOF)
	{
		buffer[i++] = c;
	}

	printf("%s\n",buffer);

	//create server socket
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	//define address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;


	bind(server_socket, (struct sockaddr *) &server_address,sizeof(server_address));

	listen(server_socket,5);

	int client_socket;

	while(1)
	{
		client_socket = accept(server_socket,NULL,NULL);
		printf("Serving Client...\n");
		send(client_socket,buffer, sizeof(char)*(strlen(buffer)),0);
		printf("Client Served...\n");
		close(client_socket);
	}


	free(buffer);

	return 0;
}
