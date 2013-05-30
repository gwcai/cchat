#include<stdio.h>
#include"user.h"

int mount = 0;

void create_userlist()
{
	root = malloc(sizeof(struct user*));
	memset(root->name,'\0',sizeof(root->name));
	memset(root->passwd,'\0',sizeof(root->passwd));
	root->fd = 0;
	root->next = NULL;
}
int insert(struct user *node)
{
	if(root == NULL)
		create_userlist();
	p = root;
	while((p->next != NULL))
	{
		if(p->fd == node->fd)	//已经登录了
			return 0;
		p = p->next;
	}
	p->next = node;
	p = p->next;
	p->next = NULL;
	mount++;
	return 1;
}
int search(char *name)
{
	if(mount == 0) return 0;
	p = root;
	while(p->next != NULL)
	{
		p = p->next;
		if(strcmp(p->name,name) == 0)
		return 1;
	}
	return 0;
}
int delete_user(struct user *node)
{
	p = root;
	while(p->next != NULL)
	{
		if(p->next == node)
		{
			p->next = p->next->next;
			mount--;
			free(node);
			return 1;
		}			
	}
	return 0;
}
void printuser()
{
	p = root;
	printf("当前在线用户列表:\n");
	while(p->next != NULL)
	{
		p = p->next;
		printf("%s\n",p->name);
	}
}
