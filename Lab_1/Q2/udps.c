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
	char buf[1024]="Enter Your String : ";
	struct sockaddr_in serv , client;
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
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	size = sizeof(client);

	r = bind(s, (struct sockaddr *)&serv , sizeof(serv));

	if(r == -1)
	{
		printf("Socket Binding Failure \n");
		exit(0);
	}

	printf("Socket Binding Successful \n");
	// char myStr[50];
	// scanf("%s",myStr);

	while(1)
	{   

		char str[1024];
		r = recvfrom(s , str , sizeof(str) , 0 , (struct sockaddr *)&client , &size);
		printf("String Recrived is : %s\n", str);

		if(strcmp(str , "Halt") == 0)
		{
			close(s);
			exit(0);
		}
		int l = 0;
    	int h = strlen(str) - 1;
 		int x = strlen(str);

		int flag = 1;    
	    while (h > l)
	    {
	        if (str[l++] != str[h--])
	        {
	      		flag = 0;      
	        }
	    }
	    char res[1024];
    	if(flag == 1)
    	{
    		strcpy(res ,"Its A Palindrome ! ");
    	}
    	else
    		strcpy(res , "Its Not a Palindorme !");

    	r = sendto(s , res , sizeof(res) , 0 , (struct sockaddr *)&client , sizeof(client));
    	int a = 0,e = 0,o = 0,u = 0;

    	char len[4];
    	sprintf(len , "%d" , x);
    	strcpy(buf , "The Length Of String is : ");
    	strcat(buf , len);

    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

    	for(j = 0 ; j<strlen(str) ; j++)
    		{
    			if(str[j] == 'a' || str[j] == 'A')
    				a++;
    			    			
    			if(str[j] == 'e' || str[j] == 'E')
    				e++;

    			if(str[j] == 'i' || str[j] == 'I')
    				i++;

    			if(str[j] == 'o' || str[j] == 'O')
    				o++;

    			if(str[j] == 'u' || str[j] == 'U')
    				u++;
    		}

    		
    	strcpy(buf , "The Count of a is : ");
    	sprintf(len , "%d" , a);
    	strcat(buf , len);
    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

    	strcpy(buf , "The Count of e is : ");
    	sprintf(len , "%d" , e);
    	strcat(buf , len);
    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

    	strcpy(buf , "The Count of i is : ");
    	sprintf(len , "%d" , i);
    	strcat(buf , len);
    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

    	strcpy(buf , "The Count of o is : ");
    	sprintf(len , "%d" , o);
    	strcat(buf , len);
    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

    	strcpy(buf , "The Count of u is : ");
    	sprintf(len , "%d" , u);
    	strcat(buf , len);
    	r = sendto(s , buf , sizeof(buf) , 0 , (struct sockaddr *)&client , sizeof(client));

	}

	close(s);

}