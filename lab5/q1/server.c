#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
  #include <sys/types.h>
  #include <sys/wait.h>
main()
{
int s,r,recb,sntb,x,ns,a=0;
int count=0;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
char buff[500];
char content[500];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{

printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("\nSocket binded.");

r=listen(s,3);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening.");
len=sizeof(client);
	int returnVal;
	while(count<2)
	{
		ns=accept(s,(struct sockaddr*)&client, &len);
		count++;
		if(ns==-1)
		{
		close(s);
		exit(0);
		}
		printf("\nSocket accepting.\n\n");
		returnVal=fork();
		if(returnVal==0)
		{	
			recb=recv(ns,buff,sizeof(buff),0);
			printf("\n\n");
			strcat(buff," ");
			FILE *f;
			f=fopen("m.txt","a");
			fprintf(f,"%s",buff);
			fclose(f);
			printf("client number %d\n",count );
			strcpy(buff," ");
			recb=recv(ns,buff,sizeof(buff),0);
			printf("%s\n\n",buff);
			
			strcat(buff," ");
			close(s);
			
		}
		
	}
	if(count==2 && returnVal!=0)
		{
			int status=0;
			pid_t abcd;
			while((abcd=wait(&status))>0)
			{

			}
			FILE *f;
			f=fopen("m.txt","r");
			fgets(buff,100,f);
			printf("%s\n\n\n",buff);
			strcpy(buff,"terminate session");
			sntb=send(ns,buff,sizeof(buff),0);
			printf("\n\n\n");
		}	
}