#include "headers.h"
int compareNodes(const void *a, const void *b)
{
    const NodeStatus *nodeA = (const NodeStatus *)a;
    const NodeStatus *nodeB = (const NodeStatus *)b;
    return (nodeA->nodeptr->value - nodeB->nodeptr->value);
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
void printActivities(int count, NodeStatus nodes[count])
{
    for (int i = 0; i < count; i++)
    {
        if (nodes[i].running)
            printf("%d : %s - Running\n", nodes[i].nodeptr->value, nodes[i].nodeptr->name);
        else
            printf("%d : %s - Stopped\n", nodes[i].nodeptr->value, nodes[i].nodeptr->name);
    }
}
char checkState(int pid)
{
    char stat[25] = "\0";
    sprintf(stat, "/proc/%d/stat", pid);
    FILE *file = fopen(stat, "r");
    int pgrp;
    char state;
    char executable[256];
    unsigned long int vsize;
    char exe[25] = "\0";
    char TEMP[100];
    fscanf(file, "%d (%[^)]) %c %s", &pid, TEMP, &state, TEMP);
    fclose(file);
    return state;
}
void activities(command cmd)
{
    if (cmd.argc > 1)
    {
        fprintf(stderr, "\x1b[31mactivities: activities does not accept any arguments\n\x1b[0m");
        return;
    }
    int count = countNodes(bglist);
    NodeStatus nodes[count];
    PtrNode current = bglist->next;
    int status;
    for (int i = 0; i < count; i++)
    {
        nodes[i].nodeptr = current;
        char state = checkState(nodes[i].nodeptr->value);
        if (state == 'T')
        {
            nodes[i].running = false;
        }
        else
        {
            nodes[i].running = true;
        }
        current = current->next;
    }
    qsort(nodes, count, sizeof(NodeStatus), compareNodes);
    printActivities(count, nodes);
}
