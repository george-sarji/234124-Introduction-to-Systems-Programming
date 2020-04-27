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
int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
    if (list1 == NULL)
        return EMPTY_LIST;
    Node newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return MEMORY_ERROR;
    Node temp = newNode;
    // Iterate over lists
    while (list1 != NULL && list2 != NULL)
    {
        // Check which one is the smallest number.
        if (list1->x > list2->x)
        {
            // Set smaller number into node and next.
            (temp)->x = list2->x;
            list2 = list2->next;
        }
        else
        {
            (temp)->x = list1->x;
            list1 = list1->next;
        }
        // Move onto next node.
        Node nextNode = malloc(sizeof(Node));
        if (nextNode == NULL)
            return MEMORY_ERROR;
        (temp)->next = nextNode;
        temp = (temp)->next;
    }
    // Go through the lists
    while (list1 != NULL)
    {
        // Create a new node for next.
        temp->x = list1->x;
        if (list1->next != NULL)
        {
            // Allocate memory.
            Node nextNode = malloc(sizeof(Node));
            temp->next = nextNode;
            temp = temp->next;
        }
        list1 = list1->next;
    }

    while (list2 != NULL)
    {
        // Create a new node for next.
        temp->x = list2->x;
        if (list2->next != NULL)
        {
            // Allocate memory.
            Node nextNode = malloc(sizeof(Node));
            temp->next = nextNode;
            temp = temp->next;
        }
        list2 = list2->next;
    }
    *merged_out = newNode;
    return SUCCESS;
}

int getListLength(Node list)
{
    int count = 0;
    if (list == NULL)
        return count;
    while (list != NULL)
    {
        count++;
        list = list->next;
    }

    return count;
}

bool isListSorted(Node list)
{
    if (list == NULL)
        return true;
    while (list->next != NULL)
    {
        if (list->x > list->next->x)
            return false;
    }
    return true;
}

int main()
{
    // Create list1
    Node list1 = malloc(sizeof(Node));
    if (list1 == NULL)
    {
        return -1;
    }
    (list1)->x = 1;
    (list1->next) = malloc(sizeof(Node));
    (list1)->next->x = 4;
    (list1)->next->next = malloc(sizeof(Node));
    (list1)->next->next->x = 9;

    Node list2 = malloc(sizeof(Node));
    (list2)->x = 2;
    (list2)->next = malloc(sizeof(Node));
    (list2)->next->x = 4;
    (list2)->next->next = malloc(sizeof(Node));
    (list2)->next->next->x = 8;
    Node merged = NULL;
    ErrorCode result = mergeSortedLists(list1, list2, &merged);
    if (result == SUCCESS)
    {
        printf("Success!!!");
    }
    return 0;
}