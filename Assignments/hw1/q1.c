#include <stdlib.h>
#include <stdbool.h>

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
int getListLength(Nodelist);
bool isListSorted(Nodelist);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
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