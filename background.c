#include "headers.h"
struct Node *createNode(char *name, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Could not create background process list\n");
        exit(EXIT_FAILURE);
    }
    mystrcpy(newNode->name, name);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
struct Node *initializeList()
{
    struct Node *dummy = createNode("DUMMY", 0);
    return dummy;
}
void insertNode(struct Node *head, char *name, int value) {
    struct Node *newNode = createNode(name, value);    
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}
