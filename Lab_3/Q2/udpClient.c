#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
	char buf[1024];

	int s , p;

	struct sockaddr_in serv , client;
	socklen_t size;

	printf("Enter Port Number : ");
	scanf("%d",&p);
	printf("\n");

	s = socket(AF_INET , SOCK_DGRAM , 0);

	if( s == -1 )
	{
		printf("Socket nahi bana ....\n");
		exit(0);
	}
	
	printf("Socket bann gaya ......\n");

	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");


	printf("Permutation Karwana hai ??? Lekin Kyu ??? \n");
	printf("Aacha theek hai Word likh dena mai dekhta hun kya ho sakta hai >>  ");
	wapis: scanf("%s" , buf);
	int sd;
	sd =  sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr * )&serv , sizeof(serv));

	if ( sd < 0 )
	{
		printf(" Word nahi gaya ......\n");
		printf("Wapis se likhna wo word ......\n");
		goto wapis; 
	}
	else
	{
		printf("Word bhej diya hai ab server mein dekhlena permutations ke liye ...... \n");
		printf("Thanks to bol do ......\n");
	
	}

	close(s);
}