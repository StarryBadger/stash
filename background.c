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
    newNode->running = true;
    return newNode;
}
Node *initializeList()
{
    Node *dummy = createNode("DUMMY", 0);
    return dummy;
}

void insertNode(Node *head, char *name, int value, bool running)
{
    Node *newNode = createNode(name, value);
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    current->running = running;
}
void stopNode(PtrNode head, int valueToRemove, bool successfulExit)
{
    PtrNode current = head;
    PtrNode previous = NULL;
    while (current != NULL)
    {
        if (current->value == valueToRemove)
        {
            if (successfulExit)
            {
                printf("%s exited normally (%d)\n", current->name, current->value);
            }
            else
            {
                printf("%s exited abnormally (%d)\n", current->name, current->value);
            }
            current->running = false;
            DEBUG
            current = current->next;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}
void removeDeadNodes(PtrNode head)
{
    PtrNode previous = head;
    PtrNode current = head->next;
    while (current != NULL)
    {
        if (current->running == false)
        {
            PtrNode temp = current;
            previous->next = current->next;
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
    int status;
    PtrNode current = bglist->next;
    PtrNode previous = bglist;
    while (current != NULL)
    {
        if (waitpid(current->value, &status, WNOHANG | WUNTRACED) != 0)
        {
            if (WIFEXITED(status))
            {
                printf("%s exited normally (%d)\n", current->name, current->value);
            }
            else
            {
                printf("%s exited abnormally (%d)\n", current->name, current->value);
            }
            current->running = false;
            current = current->next;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
    int count = countNodes(bglist);
    PtrNode nodes[count];
    PtrNode current1 = bglist->next;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current1;
        current1 = current1->next;
    }
    qsort(nodes, count, sizeof(Node), compareNodes);
}