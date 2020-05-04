#ifndef NODE_H
#define NODE_H

typedef struct node_t
{
    struct pair_t *data;
    struct node_t *next;
} * Node;

typedef struct pair_t
{
    const char *key;
    const char *value;
} * MapPair;

#endif