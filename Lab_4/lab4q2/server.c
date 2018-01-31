#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
main()
{
int s,r,recb,sntb,x,ns,a=0;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{printf("\nSocket creation error.");
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
r=listen(s,1);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening.");
len=sizeof(client);
ns=accept(s,(struct sockaddr*)&client, &len);
if(ns==-1)
{
close(s);
exit(0);
}
printf("\nSocket accepting.");
printf("\n\n");
	recb=recv(ns,buff,sizeof(buff),0);
	printf("%s\n",buff );
	FILE *f;
	f=fopen("dns.txt","r");
	char line[40];
	int flag1=0;
	while(fgets(line,sizeof(line),f)!=NULL)
	{
		
		int i;
		int flag=1;
		char temp[50];
		for(i=0;i<9;i++)
		{
			if(buff[i]!=line[i])
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			for(i=10;i<strlen(line);i++)
				temp[i-10]=line[i];
			temp[i-10]='\0';
			sntb=send(ns,temp,sizeof(temp),0);
			flag1=1;
			break;
		}

		
	}
	if(flag1==0)
	{
		strcpy(buff,"no domain found");
		sntb=send(ns,buff,sizeof(buff),0);
	}

}








