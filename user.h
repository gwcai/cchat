#include<stdlib.h>
#include<string.h>

typedef struct user{
        char name[20];
        int fd;
        char passwd[10];
        struct user *next;
}user;

int inituser(user **root);
int insert(user **root,user *node);
int delete_user(user *root,char *name);
int search(user *root,char *name);
void printuser(user *root);
