#ifndef __BACKGROUND_H
#define __BACKGROUND_H
typedef struct Node
{
    char name[64];
    int value;
    struct Node *next;
}Node;
typedef Node* PtrNode;
void insertNode(struct Node *head, char *name, int value);
struct Node *initializeList();
struct Node *createNode(char *name, int value);
void findKilled();
void removeNode(PtrNode head, int valueToRemove);
#endif