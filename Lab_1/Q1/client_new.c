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

	
	printf("%s", "Enter The size of array ");
	scanf("%d" , &k);
	printf("\n");

	char sz[3];
	sprintf(sz , "%d" , k);

	f = send(s , sz , sizeof(sz) , 0);

	printf("%s\n", "Enter Array Elements : ");

	for(i=0 ; i<k ; i++)
	{
		scanf("%d" , &arr[i]);
		buf[i] = arr[i] + '0';
	}

	int t = send(s , buf , sizeof(buf) , 0);

	if( j == 1)
	{
		recv(s , buf , sizeof(buf) , 0);
		printf("%s\n", buf);

		char ch[3];
		int c;
		scanf("%d" , &c);

		sprintf(ch , "%d" ,c);
		send(s , ch ,sizeof(ch) , 0);

		char res[10];
		recv(s , res , sizeof(res) , 0);
		printf("%s\n", res);
	}
	if(j == 2)
	{
		recv(s , buf , sizeof(buf) , 0);
		int num = atoi(buf);

		for(int m=0 ;m<k ; m++)
		{
			b[k-m-1] = num%10;
			num = num/10;
		}

		printf("Ascending Sorted Array Received is \n");

		for(int l=0 ; l<k ; l++)
	 	{
	 		printf("%d " , b[l]);
		}
		printf("\n");
	}

	if(j == 3)
	{
		recv(s , buf , sizeof(buf) , 0);
		int num = atoi(buf);

		for(int m=0 ;m<k ; m++)
		{
			b[k-m-1] = num%10;
			num = num/10;
		}

		printf("Descending Sorted Array Received is \n");

		for(int l=0 ; l<k ; l++)
	 	{
	 		printf("%d " , b[l]);
		}
		printf("\n");
	}


	close(s);

}