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
	char opt[1024] = "1. Search \n2. Sort Ascending \n3. Sort Decending \n4. Exit \n ";
	char buf[1024]="";

	int i , j , k , s, r , p;

	struct sockaddr_in serv;
	struct sockaddr_in client;
	socklen_t size;

	printf("%s", "Enter Port Number : ");
	scanf("%d" , &p);
    printf("\n");
	s = socket(AF_INET , SOCK_STREAM , 0);

	if( s == -1 )
	{
		printf("%s\n","Socket Creation Error ");
		exit(0);
	}

	printf("%s\n", "Socket Created");

	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
    //printf("DWSds");
	k = bind(s , (struct sockaddr *)&serv , sizeof(serv));

	if( k == -1 )
	{
		printf("%s\n", "Socket Binding Error");
		exit(0);
	} 

	else 
	{
		printf("%s\n", "Socket Binding ");
	}

	if( listen(s , 5) == 0 )
	{
		printf("%s\n", "Listening");
	} 
	else
	{
		printf("%s\n", "Listening Failure ");
		close(s);
		exit(0);
	}

	size = sizeof(client);

	int ns = accept(s , (struct sockaddr *)&client , &size);

	if( ns == -1 )
	{
		printf("%s\n", "Cannot accept any connections ");
		close(s);
		exit(0);
	}

	else
	 {
	 	printf("%s\n", "Accepting ");
	 }

	 int d = send(ns , opt , sizeof(opt) , 0);

	 printf("Option Received = ");
	 char op[3];
	 int f = recv(ns ,op , sizeof(op) , 0);
	 int o;
	 sscanf(op , "%d" , &o);
	 printf("%d\n", o);

	  if(o == 4)
	 {
	 	exit(0);
	 }
	 
	 printf("%s","Array Size Entered is = ");
	 char sz[3];
	 f = recv(ns , sz , sizeof(sz) , 0);
	 int ss;
	 sscanf(sz , "%d" , &ss);
	 printf("%d\n", ss);
	 int b[10] = {0};
	int arr[10] = {0};
	 int t = recv(ns , buf , sizeof(buf) , 0);

	 printf("String Received = %s \n" , buf);

    //for(int q=0;q<sizeof(buf);q++)
      // {
       	//arr[q]=atoi(buf[q]);
       //}
	 int num = atoi(buf);
      
	 for(int l=0 ; l<ss ; l++)
	 {
	 	arr[ss-l-1] = num%10;
	 	num = num/10;
	 }
	 
	 printf("Array Received is \n");
	 for(int l=0 ; l<ss ; l++)
	 {
	 	printf("%d " , arr[l]);
	 }
	 printf("\n");

	 if(o == 1)
	 {
	 	strcpy(buf , "Enter Number To Search : ");
	 	send(ns , buf , sizeof(buf) , 0);

	 	int c;
	 	char ch[3];

	 	recv(ns , ch , sizeof(ch) , 0);
	 	printf("Number To Be Searched is : %s \n" , ch);

	 	sscanf(ch , "%d" , &c);

	 	char res[10];

	 	int g = 0;
	 	for(int q=0 ; q<ss ; q++)
	 	{
	 		if(arr[q] == c)
	 			g = 1;	 		    
	 	}
	 	if(g == 1)
	 		strcpy(res,"Found \n");
	 	else
	 		strcpy(res ,"Not Found\n");

	 	send(ns , res , sizeof(res) , 0);
	 }

	 if(o == 2)
	 {
	 	for(int m=ss-1 ; m>0 ; m--)
	 	{
	 		for(int h = 0 ; h < m ; h++)
	 		{
	 			if(arr[h]>arr[h+1])
	 			{
	 				int temp = arr[h];
	 				arr[h] = arr[h+1];
	 				arr[h+1] = temp;
	 			}
	 		}
	 	}
	 	for(int m=0 ; m<ss ; m++)
	 	{
	 		buf[m] = arr[m] + '0';
	 		printf("%d " , arr[m]);
	 	}
	 	printf("\n");
	 	
	 	send(ns , buf , sizeof(buf) , 0);	
	 }

	 if(o == 3)
	 {
	 	for(int m=ss-1 ; m>0 ; m--)
	 	{
	 		for(int h = 0 ; h < m ; h++)
	 		{
	 			if(arr[h]>arr[h+1])
	 			{
	 				int temp = arr[h];
	 				arr[h] = arr[h+1];
	 				arr[h+1] = temp;
	 			}
	 		}
	 	}
	 	for(int m=0 ; m<ss ; m++)
	 	{
	 		b[ss-m-1] = arr[m];
	 		//printf("%d ", arr[m]);
	 	}
	 	for(int m=0 ; m<ss ; m++)
	 	{
	 		
	 		buf[m] = b[m] + '0';
	 		printf("%d " , b[m]);
	 	}
	 	printf("\n");

	 	send(ns , buf , sizeof(buf) , 0);
	 }
	
	 close(ns);
	 close(s);

}
