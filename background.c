#include "headers.h"
Node *createNode(char *name, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "\x1b[31mCould not create background process list\n\x1b[0m");
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
void findKilled()
{
    int status;
    PtrNode current = bglist->next;
    PtrNode previous = bglist;
    while (current != NULL)
    {
        if (waitpid(current->value, &status, WNOHANG | WUNTRACED) !=0)
        {
            if (WIFEXITED(status))
            {
                printf("%s exited normally (%d)\n", current->name, current->value);
            }
            else
            {
                printf("%s exited abnormally (%d)\n", current->name, current->value);
            }
            if (previous == NULL)
            {
                bglist = current->next;
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
void removeNode(PtrNode head, int valueToRemove)
{
    PtrNode current = head;
    PtrNode previous = NULL;
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
