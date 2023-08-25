#ifndef __BACKGROUND_H
#define __BACKGROUND_H
struct Node
{
    char name[64];
    int value;
    struct Node *next;
};
void insertNode(struct Node *head, char *name, int value);
struct Node *initializeList();
struct Node *createNode(char *name, int value);

#endif