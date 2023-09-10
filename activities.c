#include "headers.h"
int compareNodes(const void *a, const void *b)
{
    const Node *nodeA = (const Node *)a;
    const Node *nodeB = (const Node *)b;
    return (nodeA->value - nodeB->value);
}
int countNodes(PtrNode head)
{
    int count = 0;
    PtrNode current = head->next;
    while (current != NULL)
    {
        ++count;
        current = current->next;
    }
    return count;
}
void printActivities(int count, PtrNode nodes)
{
    for (int i = 0; i < count; i++)
    {
        if (nodes->running)
            printf("%d : %s - Running", nodes->value, nodes->name);
        else
            printf("%d : %s - Running", nodes->value, nodes->name);
    }
}
void activities(command cmd)
{
    if (cmd.argc > 1)
    {
        fprintf(stderr, "\x1b[31mactivities: activities does not accept any arguments\n\x1b[0m");
        return;
    }
    int count = countNodes(bglist);
    PtrNode nodes[count];
    PtrNode current = bglist->next;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->next;
    }
    qsort(nodes, count, sizeof(Node), compareNodes);
}
