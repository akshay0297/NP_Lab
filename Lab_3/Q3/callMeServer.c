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
#include <ctype.h>
#include <sys/wait.h>

char* sortString(char *a , int n)
{
	int i , j;

	for (i = 0; i < n; i++)
	 {
	 	for ( j = i+1; j < n; j++)
	 	{
	 		if(a[i] > a[j])
	 		{
	 			char temp = a[i];
	 			a[i] = a[j];
	 			a[j] = temp;

	 		}
	 	}
	 }

	 return a; 
} 

int  main()
{
	char buf[1024] , str[1024] = "";

	struct sockaddr_in  serv , client;
	socklen_t size;

	int status;

	printf("Enter Port Number : ");
	int p ;
	scanf("%d" , &p);
	printf("\n");

	int s;
	s = socket(AF_INET , SOCK_STREAM , 0);
	if( s == -1)
	{
		printf("Socket Nahi Bana :P \n");
		exit(0);
	}
	printf("Socket toh bann gaya, ab kya ?\n");

	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	int k;

	k = bind(s, (struct sockaddr *)&serv , sizeof(serv));

	if( k == -1)
	{
		printf("Bind na ho paiyega :D\n");
		exit(0);
	}


	printf("Lol Bind bhi ho gaya , ab party !!! \n");

	if(listen(s , 10) == 0)
	{
		printf("Haan bhai sunn reha hun mai ......\n");
	}
	else
	{
		printf("Mai kisi ki nahi sunnta .... ");
		close(s);
		exit(0);
	}

	int ns;

	size = sizeof(client);
	ns = accept(s , (struct sockaddr *)&client , &size);

	if(ns == -1)
	{
		printf("Hum tumhe accept nahi katre ....\n");
		close(s);
		exit(0);
	}
	printf("Ab to accept bhi kar liye maine ......\n");

	printf("Client Ek string bhejne wala tha .........\n");

	int rv = recv(ns , buf , sizeof(buf) , 0);

	if( rv < 0)
	{
		printf(" Nahi aaya abhi tak ......\n");
	}
	else
	{
		printf("%s aaya hai .....\n", buf);
	}

	char num[1024] = "";
	int i;
	for(i = 0 ; i < strlen(buf) ; i++)
	{
		if(isdigit(buf[i]))
		{
			//strcat(num , buf[i]);
			num[strlen(num)] = buf[i];
		}
		else
			if(isalpha(buf[i]))
			{
				//strcat(str , buf[i]);
				str[strlen(str)] = buf[i];
			}
	}
	printf("Saare Numbers :: %s\n" , num);
	printf("Saare letters :: %s\n" , str);

	pid_t pid;
	pid = fork();

	if( pid == 0 )
	{
		printf("Abhi main baccha hun to sirf Integers sot karunga ...... \n");
		int b = strlen(num);
		char *msg;
		msg = sortString(num , b);
		printf("Sorted Numbers are : %s \n" , msg);
		printf("Hogaya ........ \n");
		exit(10);
	}
	else if( pid > 0 )
	{
		wait(&status);
		printf("Hum baap hai , hum string sot karte hai ...........\n");
		int c = strlen(str);
		char *msg;
		msg = sortString(str , c );
		char *msg2 = (char *)malloc((c + 1)* sizeof(char));
		for(i = 0 ; i < c; i++)
		 {
		 	msg2[i] = msg[c - i -1];
		 }
		printf("Sorted string is : %s \n" , msg);
		printf("Reverse Sorted string is : %s \n" , msg2);
		printf("Hogaya bhai ...........\n");
	}
	close(ns);
	close(s);
}