#include"chat.h"

pthread_t thread;
void *sendmessage(void *arg);
char data[MAXMSG];
int main()
{
 int cfd;
 int recbytes;
 int sin_size;
 char buffer[MAXMSG];   
 struct sockaddr_in s_add;
 unsigned short portnum=0x8888; 


 cfd = socket(AF_INET, SOCK_STREAM, 0);
 if(-1 == cfd)
 {
    printf("socket fail ! \r\n");
    return -1;
 }
 printf("socket ok !\r\n");

 bzero(&s_add,sizeof(struct sockaddr_in));
 s_add.sin_family=AF_INET;
 s_add.sin_addr.s_addr= inet_addr("127.0.0.1");
 s_add.sin_port=htons(portnum);
 printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

 if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
 {
    printf("connect fail !\r\n");
    return -1;
 }
 printf("connect ok !\r\n");
 pthread_create(&thread,NULL,sendmessage,(void *)cfd);
 while(1)
{
	bzero(buffer,sizeof(buffer));
	recbytes = read(cfd,buffer,MAXMSG);
 	if(-1 == recbytes)
 	{
    		printf("read data fail !\r\n");
		return -1;
 	}else if(0 == recbytes){
		printf("the server has terminal the chat!\n");
		return 0;
	}
	else
 		printf("REC:%s\n",buffer);
}
 getchar();
 close(cfd);
 return 0;
}

void *sendmessage(void *arg)
{
 int fd = (int)arg;
 bzero(data,sizeof(data));
 while((scanf("%s",data)) != EOF)
 {
  write(fd,data,strlen(data));
 }
}
