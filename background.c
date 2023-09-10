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
    newNode->running=true;
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
void stopNode(struct Node *head, int valueToRemove, bool successfulExit)
{
    struct Node *current = head;
    struct Node *previous = NULL;
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
        }
    }
}
void removeDeadNodes(struct Node *head)
{
    struct Node *current = head;
    struct Node *previous = NULL;
    while (current != NULL)
    {
        if (!current->running)
        {
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
    while ((killed = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
    {
        if (WIFEXITED(status))
            stopNode(bglist, killed, true);
        else
            stopNode(bglist, killed, false);
    }
}