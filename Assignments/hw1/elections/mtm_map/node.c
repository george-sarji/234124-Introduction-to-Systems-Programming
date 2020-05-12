#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

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
    {
        free(node->key);
        node->key = NULL;
    }
    if (node->data != NULL)
    {
        free(node->data);
        node->data = NULL;
    }
    node->next = NULL;
    free(node);
    node = NULL;
}

Node nodeGetNext(Node node)
{
    if (node == NULL || node->next == NULL)
        return NULL;
    return node->next;
}

char *nodeGetKey(Node node)
{
    if (node == NULL || node->key == NULL)
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
        node->next = NULL;
        return NULL;
    }
    node->next = next;
    return next;
}

bool nodeCompareKey(Node node, const char *key)
{
    return node != NULL && key != NULL && nodeGetKey(node) != NULL &&
           strcmp(nodeGetKey(node), key) == 0;
}