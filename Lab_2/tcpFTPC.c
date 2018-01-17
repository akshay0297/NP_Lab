#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	int i , j , k , s, r , p;
	char buf[1024];
	int arr[1024];
	int b[1024];

	struct sockaddr_in serv;
	//socklen_t size;

	printf("Enter Port Number : ");
	scanf("%d" , &p);
	printf("\n");

	s = socket(AF_INET , SOCK_STREAM , 0);

	if( s == -1 )
	{
		printf("Socket Creation Error \n");
		exit(0);
	}

	printf("Socket Created \n");

	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	k = connect(s , (struct sockaddr *) &serv  , sizeof(serv));

	if(k == -1)
	{
		printf("%s\n", "Cannot Connect To Server");
		close(s);
		exit(0);
	}

	printf("%s\n", "Connection Successful ");

	char opt[1024];

	r = recv(s , opt , sizeof(opt) , 0);

	printf("%s\n", opt);

	printf("%s", "Enter Choice : ");
	scanf("%d" , &j);

	char op[3];
	sprintf(op , "%d" , j);
	int f = send(s , op , sizeof(op) , 0);

 	if( j == 4)
	{
		exit(0);
	}

	printf("%s", "Enter file name : ");
	scanf("%s" , buf);

	int sd = send(s , buf , sizeof(buf) , 0);

	printf("\n\n");
	recv(s , buf , 1024 , 0);
	printf("%s\n", buf);
	printf("\n");

	if( j == 1 )
	{
		printf("Enter String to be searched : ");
		char src[1024];
		scanf("%s" , src);
		printf("\n");

		send(s , src ,sizeof(src) , 0);

		recv(s , buf , sizeof(buf) , 0);

		printf("%s\n", buf);
	}

	if (j == 2)
	{
		printf("Enter the string to be replaced : ");
		char str1[1024] , str2[1024];
		scanf("%s" , str1);

		printf("\nEnter New String : ");
		scanf("%s" , str2);

		send(s , str1 , sizeof(str1) , 0);
		send(s , str2 , sizeof(str2) , 0);

		recv(s , buf , 1024 , 0);
		printf("\nModified String is \n\n%s\n\n", buf);
	}

	if(j == 3)
	{
		recv(s , buf , 1024 , 0);
		printf("The ASCII SORTED STRING IS --------> \n\n%s\n\n",buf);
	}
	close(s);
}