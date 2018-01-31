#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct Student{
int regNo;
char name[50];
int subCode;
char address[50];
char dept[50];
int semester;
char section[1];
char courses[3][50];
int sub1mark;
int sub2mark;
int sub3mark;
};

main()
{
struct Student aditya;
aditya.regNo=150953050;
strcpy(aditya.name,"aditya");
aditya.subCode=0;
strcpy(aditya.address,"varanasi");
strcpy(aditya.dept,"ICT");
aditya.semester=6;
strcpy(aditya.section,"A");
strcpy(aditya.courses[0],"NNFL");
strcpy(aditya.courses[1],"PR");
strcpy(aditya.courses[2],"DMPA");
aditya.sub1mark=100;
aditya.sub2mark=99;
aditya.sub3mark=98;

int s,r,recb,sntb,x,ns,a=0;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
char buff2[50];
strcpy(buff2,"");
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
	printf("\n\n");
	recb=recv(ns,buff,sizeof(buff),0);
	printf("\n");
	printf("%s",buff);
	printf("\n");
	
	int returnVal1=-1,returnVal2=-1,returnVal3=-1;
	int forking;
	returnVal1=fork();
	//the following code is just  showing that i know how to create mutilple childs.
	if(returnVal1>0)
	{
		returnVal2=fork();
		if(returnVal2>0)
		{
			returnVal3=fork();
			if(returnVal3>0)
			{
			}
			else if(returnVal3==0)
			{
				printf("\nthis is child three and my process id is %d\n",getpid());
			}
			
			
		}
		else if(returnVal2==0)
		{
			printf("\nthis is child two and my process id is %d\n",getpid());
		}
		//The main job starts from here
				
		
		
		
	}
	else if(returnVal1==0)
	{
		printf("\nthis is child one and my process id is %d\n",getpid());
	}
	if(strcmp(buff,"1")==0&&returnVal1==0)
	{
		strcpy(buff2,aditya.name);
		strcat(buff2,"\n");
		strcat(buff2,aditya.address);
		strcat(buff2,"\nAnd pid is");
		char temp[50];

		sprintf(temp,"%d",getpid());
		strcat(buff2,temp);
		strcat(buff2,"\n");
		printf("\n\n");
		sntb=send(ns,buff2,sizeof(buff2),0);
	}
	if(strcmp(buff,"2")==0&&returnVal2==0)
	{
		char temp[50];
		strcpy(buff2,aditya.dept);
		strcat(buff2,"\n");
		strcat(buff2,aditya.section);
		strcat(buff2,"\n");
		sprintf(temp,"%d",aditya.semester);
		strcat(buff2,temp);
		strcat(buff2,"\n");
		strcat(buff2,aditya.courses[0]);
		strcat(buff2,"\n");
		strcat(buff2,aditya.courses[1]);
		strcat(buff2,"\n");
		strcat(buff2,aditya.courses[2]);

		strcat(buff2,"\nAnd pid is");
		

		sprintf(temp,"%d",getpid());
		strcat(buff2,temp);
		strcat(buff2,"\n");
		printf("\n\n");
		sntb=send(ns,buff2,sizeof(buff2),0);
	}
	if(strcmp(buff,"3")==0&&returnVal3==0)
	{
		char temp[50];
		sprintf(temp,"%d",aditya.sub1mark);
		strcat(buff2,temp);
		strcat(buff2,"\n");
		sprintf(temp,"%d",aditya.sub2mark);
		strcat(buff2,temp);
		strcat(buff2,"\n");
		sprintf(temp,"%d",aditya.sub3mark);
		strcat(buff2,temp);
		strcat(buff2,"\n");		
		strcat(buff2,"\nAnd pid is");
		

		sprintf(temp,"%d",getpid());
		strcat(buff2,temp);
		strcat(buff2,"\n");
		printf("\n\n");
		sntb=send(ns,buff2,sizeof(buff2),0);
	}
	
}








