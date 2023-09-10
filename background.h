#ifndef __BACKGROUND_H
#define __BACKGROUND_H
typedef struct Node
{
    char name[64];
    int value;
    struct Node *next;
    bool running;
}Node;
typedef Node* PtrNode;
void insertNode(struct Node *head, char *name, int value, bool running);
struct Node *initializeList();
struct Node *createNode(char *name, int value);
void findKilled();
void stopNode(struct Node *head, int valueToRemove, bool successfulExit);
void removeDeadNodes();
#endif