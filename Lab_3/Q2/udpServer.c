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

// swap aur permute geeksforgeeks se liya hai 

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r)
{
   int i;
   if (l == r)
     printf("%s\n", a);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); 
       }
   }
}


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
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	int k;

	k = bind(s , (struct sockaddr *)&serv , sizeof(serv));

	size = sizeof(client);

	if( k == -1 )
	{
		printf("Bind nahi hua ......\n");
		exit(0);
	}

	printf("Bind ho gaya .....\n");

	int rv;

	rv = recvfrom(s , buf , sizeof(buf) , 0 , (struct sockaddr * )&client , &size);

	printf("Client ne bheja :: %s \n" , buf);
	printf("Permutation Start ho reha hai ......\n");

	int n = strlen(buf);

	permute(buf , 0 , n-1);

	close(s);
}
