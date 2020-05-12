#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node_t
{
    int x;
    struct node_t *next;
} * Node;
typedef enum
{
    SUCCESS = 0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

ErrorCode chainLinkList(Node *source, Node list)
{
    if (source == NULL || list == NULL)
    {
        return SUCCESS;
    }
    // Go through the current list.
    Node temp = (*source);
    while (list != NULL)
    {
        // Allocate next node.
        Node new_node = malloc(sizeof(*temp));
        if (new_node == NULL)
        {
            return MEMORY_ERROR;
        }
        new_node->x = list->x;
        temp->next = new_node;
        list = list->next;
        temp = new_node;
    }
    temp->next = NULL;
    return SUCCESS;
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
    if (list1 == NULL || list2 == NULL)
    {
        return EMPTY_LIST;
    }
    // Allocate new node.
    Node node = malloc(sizeof(*node));
    if (node == NULL)
    {
        return MEMORY_ERROR;
    }
    *merged_out = node;
    // Get first.
    Node temp = node;
    if (list1->x > list2->x)
    {
        // Set from list 2.
        temp->x = list2->x;
        list2 = list2->next;
    }
    else
    {
        temp->x = list1->x;
        list1 = list1->next;
    }
    while (list1 != NULL && list2 != NULL)
    {
        // Allocate new temp node.
        Node new_node = malloc(sizeof(*new_node));
        if (new_node == NULL)
        {
            *merged_out = NULL;
            return MEMORY_ERROR;
        }
        temp->next = new_node;
        if (list1->x > list2->x)
        {
            // Set from list 2.
            new_node->x = list2->x;
            list2 = list2->next;
        }
        else
        {
            new_node->x = list1->x;
            list1 = list1->next;
        }
        temp = temp->next;
    }

    if (chainLinkList(&temp, list1) == MEMORY_ERROR || chainLinkList(&temp, list2) == MEMORY_ERROR)
    {
        *merged_out = NULL;
        return MEMORY_ERROR;
    }
    return SUCCESS;
}

// int main()
// {
//     // Create list1
//     Node list = malloc(sizeof(Node));
//     if (list == NULL)
//     {
//         return -1;
//     }
//     Node tmp = list;
//     for (int i = 0; i < 5; i++)
//     {
//         tmp->x = i;
//         tmp->next = malloc(sizeof(Node));
//         tmp = tmp->next;
//     }
//     Node list2 = malloc(sizeof(Node));
//     if (list2 == NULL)
//     {
//         return -1;
//     }

//     tmp = list2;
//     for (int i = 50; i < 55; i++)
//     {
//         tmp->x = i;
//         tmp->next = malloc(sizeof(Node));
//         tmp = tmp->next;
//     }
//     Node merged = NULL;
//     ErrorCode result = mergeSortedLists(list, list2, &merged);
//     if (result == SUCCESS)
//     {
//         printf("Success!!!");
//     }
//     return 0;
// }