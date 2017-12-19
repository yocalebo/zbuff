#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#define BUFFER 1048576 //1MB sized buffer, eventually make this CLI option
#define PORT 7000   //static port number, eventually make this CLI option
 
int main (int argc, char* argv[])
{
	int connSock;
	int in;
	int i;
	int ret;
	int flags;
	struct sockaddr_in servaddr;
	struct sctp_status status;
	char buffer[BUFFER+1];
	int datalen = 0;
 	
	//ask user for data to be sent
	fprintf(stdout, "Enter data to be sent\n");
	fgets(buffer, BUFFER, stdin);
	
	//clear new line, and/or carriage return from input
	buffer[strcspn(buffer, "\r\n")] = 0;
	datalen = strlen(buffer);

	connSock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
	if (connSock == -1)
	{
		fprintf(stderr, "Function socket() failed!\n");
		exit(1);
	}
 	
	//initialize servaddr struct and fill it with 0's
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.231");

	ret = connect(connSock, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (ret == -1)
	{
		fprintf(stderr, "Function connect() failed!\n");
		close(connSock);
		exit(1);
	}
	
	ret = sctp_sendmsg(connSock, (void *) buffer, (size_t) datalen, NULL, 0, 0, 0, 0, 0, 0);
	if(ret == -1)
	{
		fprintf(stderr, "Function sctp_sendmsg() failed!\n");
		exit(1);
	}
	else
	{
		printf("Successfully sent %d bytes of data to the server!\n", ret);
	}
	
	close(connSock);
	
	return 0;
}
