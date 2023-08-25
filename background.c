#include "headers.h"
Node *createNode(char *name, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
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
Node *initializeList()
{
    Node *dummy = createNode("DUMMY", 0);
    return dummy;
}

void insertNode(Node *head, char *name, int value)
{
    Node *newNode = createNode(name, value);
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}
