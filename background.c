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

void insertNode(PtrNode head, char *name, int value)
{
    PtrNode newNode = createNode(name, value);
    PtrNode tempPtr=head->next;
    head->next=newNode;
    newNode->next=tempPtr;
}
void findKilled()
{
    int status;
    PtrNode current = bglist->next;
    PtrNode previous = bglist;
    while (current != NULL)
    {
        char state = checkState(current->value);
        if (state == 'Z')
        {
            removeNode(bglist, current->value);
        }
        current = current->next;
    }
}
void removeNode(PtrNode head, int valueToRemove)
{
    PtrNode current = head->next;
    PtrNode previous = head;
    int status;
    while (current != NULL)
    {
        if (current->value == valueToRemove && waitpid(current->value, &status, WNOHANG | WUNTRACED) != 0)
        {
            if (WIFEXITED(status))
            {
                printf("%s exited normally (%d)\n", current->name, current->value);
            }
            else
            {
                printf("%s exited abnormally (%d)\n", current->name, current->value);
            }
            previous->next = current->next;
            PtrNode temp = current;
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
