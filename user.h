#include<stdlib.h>
#include<string.h>

struct user{
        char name[20];
        int fd;
        char passwd[10];
        struct user *next;
}user,*root,*p;

void create_userlist();
int insert(struct user *node);
int delete_user(struct user *node);
int search(char *name);
void printuser();
