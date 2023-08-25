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
// pid_t tokill
// while (tokill=waitpid(child, &status, 0))>0
// print-killed
void removeNode(struct Node *head, int valueToRemove)
{
    struct Node *current = head;
    struct Node *previous = NULL;
    while (current != NULL)
    {
        if (current->value == valueToRemove)
        {
            printf("%s exited normally (%d)\n", current->name, current->value);
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}
void findKilled()
{
    pid_t killed;
    int status;
    while ((killed = waitpid(-1, &status,WNOHANG)) > 0)
    {
        removeNode(bglist, killed);
    }
}