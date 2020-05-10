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
    if (node == NULL)
    {
        return NULL;
    }
    else if (key == NULL)
    {
        node->key = NULL;
    }
    else
    {
        // Allocate new space.
        char *new_key = malloc(sizeof(char) * (1 + strlen(key)));
        if (new_key == NULL)
        {
            node->key = NULL;
        }
        else
        {
            strcpy(new_key, key);
            char *old_key = node->key;
            node->key = new_key;
            free(old_key);
        }
    }
    return node->key;
}
char *nodeSetData(Node node, const char *data)
{
    if (node == NULL)
    {
        return NULL;
    }
    else if (data == NULL)
    {
        node->data = NULL;
    }
    else
    {
        // Allocate new space.
        char *new_data = malloc(sizeof(char) * (1 + strlen(data)));
        if (new_data == NULL)
        {
            node->data = NULL;
        }
        else
        {
            strcpy(new_data, data);
            char *old_data = node->data;
            node->data = new_data;
            free(old_data);
        }
    }
    return node->data;
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