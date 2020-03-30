//
// Created by George on 3/23/2020.
//
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter size of input:\n");
    int size = 0;
    if (scanf("%d", &size) == 0 || size <= 0)
    {
        printf("Invalid size\n");
        return 0;
    }
    printf("Enter numbers:\n");
    int *array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        int currentNum = 0;
        if (scanf("%d", &currentNum) != 1)
        {
            printf("Invalid number\n");
            free(array);
            return 0;
        }
        array[i] = currentNum;
    }
    int exponentSum = 0;
    for (int i = 0; i < size; i++)
    {
        int divide = array[i];
        //        Check if number is exponent of two.
        int j = 1;
        if (divide == 1)
        {
            printf("The number %d is a power of 2: %d = 2^%d\n", array[i], array[i], 0);
            continue;
        }
        while (divide > 2 && divide % 2 == 0)
        {
            j++;
            divide /= 2;
        }

        if (divide == 2)
        {
            //            Is exponent. Add to sum.
            exponentSum += j;
            printf("The number %d is a power of 2: %d = 2^%d\n", array[i], array[i], j);
        }
    }

    printf("Total exponent sum is %d\n", exponentSum);
    return 0;
}
