#ifndef __ACTIVITIES_H_
#define __ACTIVITIES_H_
typedef struct NodeStatus
{
    PtrNode nodeptr;
    bool running;
} NodeStatus;
int compareNodes(const void *a, const void *b);
int countNodes(PtrNode head);
void printActivities(int count, NodeStatus *nodes);
void activities(command cmd);
#endif