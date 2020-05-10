#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
} * Node;

void nodeDestroy(Node node);
Node nodeCreate();
Node nodeGetNext(Node node);
char *nodeGetData(Node node);

Node nodeCreate()
{
    Node node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    node->key = NULL;
    node->value = NULL;
    return node;
}
void nodeDestroy(Node node)
{
    if (node == NULL)
        return;
    free(node->key);
    free(node->value);
    free(node);
}

Node nodeGetNext(Node node)
{
    return node->next;
}

char *nodeGetKey(Node node)
{
    return node->key;
}

char *nodeGetData(Node node)
{
    return node->value;
}
#endif