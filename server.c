#include "chat.h"
#include "user.h"
#include "server.h"

void *send_data(void *arg);
void *recv_data(void *arg);
void *beforechat(void *arg);
pthread_t thread[MAXTHREAD];
int count = 0;
char data[MAXMSG];
char recvdata[MAXMSG];

int main()
{
 int sfd,nfd;
 struct sockaddr_in s_add,c_add;
 int sin_size;
 unsigned short portnum=0x8888;
 printf("Hello,welcome to my server !\r\n");
 sfd = socket(AF_INET, SOCK_STREAM, 0);
 if(-1 == sfd)
 {
    printf("socket fail ! \r\n");
    return -1;
 }
 printf("socket ok !\r\n");


 bzero(&s_add,sizeof(struct sockaddr_in));
 s_add.sin_family=AF_INET;
 s_add.sin_addr.s_addr=htonl(INADDR_ANY);
 s_add.sin_port=htons(portnum);

 if(-1 == bind(sfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
 {
    printf("bind fail !\r\n");
    return -1;
 }
 printf("bind ok !\r\n");

 if(-1 == listen(sfd,LISNUM))
 {
    printf("listen fail !\r\n");
    return -1;
 }
 printf("listen ok\r\n");

 while(1)
 {
  sin_size = sizeof(struct sockaddr_in);

  nfd = accept(sfd, (struct sockaddr *)(&c_add), &sin_size);
  if(-1 == nfd)
 {
    printf("accept fail !\r\n");
    return -1;
 }
 printf("accept ok!\r\nServer start get connect from %#x : %d\r\n",c_add.sin_addr.s_addr,c_add.sin_port);


 if(-1 == write(nfd,"hello,welcome to my server",27))
 {
    printf("write fail!\r\n");
    return -1;
 }
 printf("write ok!\r\n");
 pthread_create(thread+(count++),NULL,beforechat,(void *)nfd);
 pthread_create(thread+(count++),NULL,recv_data,(void *)nfd);
 pthread_create(thread+(count++),NULL,send_data,(void *)nfd); 
}
 if(nfd)
	close(nfd);
 close(sfd);
return 0;
}
void *send_data(void *arg)
{
	int fd = (int)arg;
	bzero(data,sizeof(data));
	while((scanf("%s",data)) != EOF)
 	{
		if(strncmp("quit",data,4) == 0)
			break;
  		write(fd,data,strlen(data));
 	}
	close(fd);
}
void *recv_data(void *arg)
{
	int fd = (int)arg;
	int recbytes;
	bzero(recvdata,sizeof(recvdata));
	while(1)
	{
		recbytes = read(fd,recvdata,MAXMSG);	
		if(-1 == recbytes)
 		{
    			printf("read data fail !\r\n");
			close(fd);
    			return ;
 		}else if(0 == recbytes){
			printf("the other side has terminal the chat!\n");
			break;
		}
		else
 			printf("REC:%s\n",recvdata);
	}
	close(fd);
}
void *beforechat(void *nfd)
{
	int fd = (int)nfd;
	int ret = 0;
	struct user *node;
	while(1)
	{
		write(fd,buf1,strlen(buf1));
		read(fd,name,strlen(name));
		ret = search(name);
		if(!ret){
			node = malloc(sizeof(struct user));
			strcpy(node->name,name);
			node->fd = fd;
			bzero(node->passwd,sizeof(node->passwd));
			node->next = NULL;
			if(insert(node))  //插入链表
				write(fd,buf4,strlen(buf4));
			else write(fd,buf3,strlen(buf3)); 
			break;
		}else{
			write(fd,buf2,strlen(buf2));
		}
	}
}
