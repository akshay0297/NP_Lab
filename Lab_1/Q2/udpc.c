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

	printf("Enter Port Number : ");
	scanf("%d " , &p);
	

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
		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);
		
		char str[1024];
		scanf("%s" , str);
		
		r = sendto(s , str , sizeof(str) , 0 , (struct sockaddr *)&serv , size);

		char res[1024];
		r = recvfrom(s , res , sizeof(res) , 0 , (struct sockaddr *)&serv , &size);

		printf("%s\n", res);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

		r = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&serv , &size);
		printf("%s ", buf);

	}
	close(s);
}