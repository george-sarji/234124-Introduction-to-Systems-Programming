#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
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

Node nodeCreate()
{
    Node node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    node->key = NULL;
    node->data = NULL;
    node->next = NULL;
    return node;
}
void nodeDestroy(Node node)
{
    if (node == NULL)
        return;
    if (node->key != NULL)
        free(node->key);
    if (node->data != NULL)
        free(node->data);
    free(node);
}

Node nodeGetNext(Node node)
{
    if (node == NULL)
        return NULL;
    return node->next;
}

char *nodeGetKey(Node node)
{
    if (node == NULL)
        return NULL;
    return node->key;
}

char *nodeGetData(Node node)
{
    if (node == NULL)
        return NULL;
    return node->data;
}

char *nodeSetKey(Node node, const char *key)
{
    free(node->key);
    char *new_key = malloc(sizeof(char) * (1 + strlen(key)));
    if (new_key == NULL)
    {
        node->key = NULL;
        return NULL;
    }
    strcpy(new_key, key);
    node->key = new_key;
    return new_key;
}
char *nodeSetData(Node node, const char *data)
{
    // Allocate new data.
    free(node->data);
    char *new_data = malloc(sizeof(char) * (1 + strlen(data)));
    if (new_data == NULL)
    {
        node->data = NULL;
        return NULL;
    }
    strcpy(new_data, data);
    node->data = new_data;
    return new_data;
}

Node nodeSetNext(Node node, Node next)
{
    if (node == NULL || next == NULL)
    {
        return NULL;
    }
    node->next = next;
    return next;
}

bool nodeCompareKey(Node node, const char *key)
{
    if (node == NULL || key == NULL || nodeGetKey(node) == NULL)
    {
        return false;
    }
    return strcmp(nodeGetKey(node), key) == 0;
}

#endif