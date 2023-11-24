#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int verifyCommandLineArgument(int c, char *v[]);
int searchInteger(int array[], int target, int start, int end);
int verifyInteger(char *input);
int getIntArrayLength(int arraySize, int numbers[]);

int main(int argc, char *argv[])
{
    if (!verifyCommandLineArgument(argc, argv))
        return 1;

    int integerDatabase[] = {1, 5, 10, 20, 50, 100, 500, 1000};

    int searchResult = searchInteger(integerDatabase, atoi(argv[1]), 0, getIntArrayLength(sizeof(integerDatabase), integerDatabase));

    if (searchResult != -1)
    {
        printf("Found at index: %i.\n", searchResult);
        return 0;
    }
        
    printf("Not Found.\n");

    return 1;
}

int getIntArrayLength(int arraySize, int numbers[])
{ 
    return arraySize / sizeof(numbers[0]);
}

int searchInteger(int array[], int target, int start, int end)
{
    if (start > end)
        return -1;

    int middle = (end + start) / 2;

    if (array[middle] == target)
        return middle;
    else if (target > array[middle])
        return searchInteger(array, target, middle + 1, end);
    else
        return searchInteger(array, target, start, middle - 1);
}

int verifyCommandLineArgument(int c, char *v[])
{
    if (c != 2)
    {
        printf("Usage: ./search value\n");
        return 0;
    }
    
    if (!verifyInteger(v[1]))
    {
        printf("Only compatible with integer inputs.\n");
        return 0;
    }

    return 1;
}

int verifyInteger(char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
        if (!isdigit(input[i]))
            return 0;

    return 1;
}