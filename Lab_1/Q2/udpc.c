#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	int i, j , k  , s , r , p;
	char buf[1024];
	struct sockaddr_in serv ;
	socklen_t size;

	printf("Enter Port Number : \n");
	scanf("%d" , &p);
	printf("\n\n");
	

	s = socket(AF_INET , SOCK_DGRAM , 0);
	if(s == -1)
	{
		printf("\nSocket Creation Failure \n");
		exit(0);
	}
	printf("\nSocket Created \n");

	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	size = sizeof(serv);
	
	while(1)
	{
		printf("%s", "Enter string to send to Server : ");
		
		char str[1024];
		scanf("%s", str);

		printf("\n");
		
		r = sendto(s , str , strlen(str) + 1 , 0 , (struct sockaddr *)&serv , size);

		if(strcmp(str , "Halt") == 0)
		{
			close(s);
			exit(0);
		}

		char res[1024];
		r = recvfrom(s , res , sizeof(res) , 0 , (struct sockaddr *)&serv , &size);

		printf("%s\n", res);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s\n ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s \n ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s \n", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s \n", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s \n", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s \n", buf);

		printf("\n");
	}
	close(s);
}