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
	char opt[1024] = "1. Search \n2. Replace \n3. Reorder \n4. Exit \n ";
	char buf[1024]="";
    char *data;
    char ca;
    char msg[1024];

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
     
	 int sd = recv(ns , buf , sizeof(buf) , 0);

	 printf("File name Received is : %s \n" , buf);
     
	 FILE * fp;
	 long lSize;

	fp = fopen ( buf , "rb" );
	if( !fp ) 
		{
			strcpy(msg , "File Not Present !");
			send(ns , msg , sizeof(msg) , 0);
			exit(1);
		}

	else
	{

		fseek( fp , 0L , SEEK_END);
		lSize = ftell( fp );
		rewind( fp );

		data = calloc( 1, lSize+1 );
		if( !data ) 
			{
				fclose(fp);
				fputs("memory alloc fails",stderr);
				exit(1);
			}

		if( 1!=fread( data , lSize, 1 , fp) )
		  {
		  	fclose(fp);
		  	free(data);
		  	fputs("entire read fails",stderr);
		  	exit(1);
		  }

		fclose(fp);
		printf("\n\n");
		printf("%s\n", data);
		printf("\n");

		send(ns , data  , 1024 , 0);
	}

		if(o == 1)
		{
			char src[1024];
			recv(ns , src ,sizeof(src) , 0);
			printf("Word to be Searched is : %s\n", src);

			int l1 = strlen(data);
			int l2 = strlen(src);
			int count = 0 ; int count1 = 0; 
			for(i=0 ; i<l1 ;)
			{
				j=0;
				count = 0;

				while((data[i] ==  src[j]))
				{
					count++;
					i++;
					j++;
				}
				if(count == l2)
				{
					count1++;
					count = 0;
				}
				else i++;
			}

			if(count1 == 0)
				{
					strcpy(msg , "String Not Found !");
					printf("%s\n", msg);
				}
			else
			{
				strcpy(msg , "Count is : ");
				char dem[3];
				sprintf(dem , "%d" , count1);
				strcat(msg , dem);
				printf("%s\n", msg);
			}

			send(ns , msg , sizeof(msg) , 0 );
		}

		if(o == 2)
		{
			char str1[1024];
			char str2[1024];

			recv(ns , str1 , sizeof(str1) ,0);
			recv(ns , str2 , sizeof(str2) , 0);

			printf("String to be replaced is : %s\n", str1);
			printf("String that replaces is  : %s\n", str2);

			char *pf;
			static char buffer[1024];

			if(!(pf = strstr(data , str1)))
			{
				printf("String to be replaced is not found \n");
				strcpy(msg , "String to be replaced is not found \n");
				send(ns , msg , sizeof(msg) ,0);
			}
			else
			{
				strncpy(buffer , data , pf-data);
				buffer[pf-data] = '\0';

				sprintf(buffer + (pf-data) , "%s%s" , str2 , pf+strlen(str1));

				printf("\nReplaced Data is : \n\n %s \n\n", buffer);
				send(ns , buffer , 1024 ,0);
			}	
		}

		if(o == 3)
		{
			char temp;
			for(int li=0;data[li];li++)
			   	 {
			        for(int lj=li+1;data[lj];lj++)
			        {
			            if(data[lj]<data[li])
			            {
			                temp=data[lj];
			                data[lj]=data[li];
			                data[li]=temp;
			            }
			        }
		    	}
		    printf("The ASCII SORTED STRING IS --------> \n\n%s\n\n",data);
		    send(ns , data , 1024 , 0);
		}
	 close(ns);
	 close(s);
}
