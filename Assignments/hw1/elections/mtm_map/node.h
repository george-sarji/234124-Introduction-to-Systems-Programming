#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct node_t
{
    char *key;
    char *data;
    struct node_t *next;
} * Node;

void nodeDestroy(Node node);
Node nodeCreate();
Node nodeGetNext(Node node);
char *nodeGetData(Node node);
char *nodeSetData(Node node, const char *data);
char *nodeSetKey(Node node, const char *key);
Node nodeSetNext(Node node, Node next);
bool nodeCompareKey(Node node, const char *key);

#endif