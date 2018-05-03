// UDP Client

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
 
#define SIZE 64

int main()
{
	int sock;
	unsigned int cli_len=0;
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	char buffer[SIZE];
	char echobuffer[SIZE];
	
	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		printf("Error Creating Socket\n");
		exit(1);
	}
	else{	printf("Socket CReated\n");}



	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(9852);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);

	printf("Enter text to send: ");
	scanf ("%[^\n]%*c", buffer);

	int slen=0;

	if((slen=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&serveraddr,sizeof(serveraddr)))<0)
		printf("Error Sending\n"),exit(1);
	else	
		printf("%d bytes Sent Successfully\n",slen);

	cli_len=sizeof(clientaddr);

	if((cli_len=recvfrom(sock,echobuffer,strlen(buffer),0,(struct sockaddr *)&clientaddr,&cli_len))<0)
		printf("Error Receiving"),exit(1);
	else
		printf("Received %d bytes\n",cli_len);

	printf("Echoed Data from Server: %s\n",echobuffer);		
}
