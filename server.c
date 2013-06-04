#include "chat.h"
#include "user.h"
#include "server.h"

void *send_data(void *arg);
void *recv_data(void *arg);
void beforechat(int fd);
pthread_t thread[MAXTHREAD];
int count = 0;
char data[MAXMSG];
char recvdata[MAXMSG];
struct user *root;

int main()
{
	int sfd,nfd;
	struct sockaddr_in s_add,c_add;
	int ret = 0;
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

	beforechat(nfd);
 
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
	pthread_exit(NULL);
}
void *recv_data(void *arg)
{
	int fd = (int)arg;
	int recbytes;
	char toall[MAXMSG];
	char *all = "TO ALL:";
	struct user *p;
	bzero(recvdata,sizeof(recvdata));
	int ret = 0;
       
	while(1)
	{
		p = root->next;
		bzero(toall,sizeof(toall));
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
		else{
 			strcat(toall,all);
			strcat(toall,recvdata);
			printf("%s\n",toall);	
			while(p != NULL)
			{
				write(p->fd,toall,strlen(toall));
				p = p->next;
			}
		}
	}
	close(fd);
	pthread_exit(NULL);
}
void beforechat(int fd)
{
	int ret = 1;
	int n;
	struct user *node;
	inituser(&root);  //初始化
	bzero(name,sizeof(name));	
	bzero(passwd,sizeof(passwd));
	write(fd,buf1,strlen(buf1));
	while((n = read(fd,name,20) <= 0))
	{
		if(n > 0) break;
		write(fd,buf1,strlen(buf1));
	}
	write(fd,buf5,strlen(buf5));
	while((n = read(fd,passwd,20) <= 0))
	{
		if(n > 0) break;
                write(fd,buf5,strlen(buf5));
	}
	printf("name:%s\n",name);
	printf("passwd:%s\n",passwd);
	ret = search(root,name);
	if(!ret){
		node = (struct user*)malloc(sizeof(struct user));
		memset(node,0,sizeof(user));
		node->next = NULL;
		strcpy(node->name,name);
		strcpy(node->passwd,passwd);
		node->fd = fd;
		if(insert(&root,node))  //插入链表
			write(fd,buf4,strlen(buf4));
		else write(fd,buf3,strlen(buf3)); 
		free(node);
		//break;
	}else{
		write(fd,buf2,strlen(buf2));
	}
}
