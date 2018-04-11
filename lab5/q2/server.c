#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
  #include <sys/types.h>
  #include <sys/wait.h>
#include<time.h>
int find_anagram(char array1[], char array2[])
{
    int num1[26] = {0}, num2[26] = {0}, i = 0;
 
    while (array1[i] != '\0')
    {
        num1[array1[i] - 'a']++;
        i++;
    }
    i = 0;
    while (array2[i] != '\0')
    {
        num2[array2[i] -'a']++;
        i++;
    }
    for (i = 0; i < 26; i++)
    {
        if (num1[i] != num2[i])
            return 0;
    }
    return 1;
}
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
char buff2[500];
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
	while(1)
	{
		ns=accept(s,(struct sockaddr*)&client, &len);
		
		printf("\nSocket accepting.\n\n");
		recb=recv(ns,buff2,sizeof(buff2),0);
		printf("%s\n",buff2);
		printf("\n\n");
		recb=recv(ns,content,sizeof(content),0);
		printf("%s\n",content);
		printf("\n\n");
		recb=recv(ns,buff,sizeof(buff),0);
		time_t current_time;
	    char* c_time_string;

	    current_time = time(NULL);

	    /* Convert to local time format. */
	    c_time_string = ctime(&current_time);

	    strcat(buff,c_time_string);
		printf("%s\n",buff);
		printf("\n\n");
		if(find_anagram(buff2,content))
		{
			printf("yes\n");
			strcpy(buff,"yes");
		}
		else
		{
			printf("no\n");
			strcpy(buff,"no");
		}
		sntb=send(ns,buff,sizeof(buff),0);
		printf("\n\n\n");
	}
}
