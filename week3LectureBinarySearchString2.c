#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringArrayLength(int arrayBitSize, char *strings[]);
int searchString(char *array[], char *target, int start, int end);
char *convertInput(int c, char *v[]);

int main(int argc, char *argv[])
{
    char *userInput = convertInput(argc, argv);

    char *names[] = {"Barros", "Carter", "David"};
    char *phoneNumbers[] = {"+55 (81) 99906-0088", "+1-617-495-1000", "+1-949-468-2750"};

    int arrayLength = getStringArrayLength(sizeof(names), names);

    int result = searchString(names, userInput, 0, arrayLength);

    if (result != -1)
    {
        printf("Phone number of %s: %s\n", names[result], phoneNumbers[result]);
        free(userInput);
        return 0;
    }
            
    printf("Not found.\n");
    free(userInput);

    return 1;
}

int searchString(char *array[], char *target, int start, int end)
{
    if (start >= end)
        return -1;

    int middle = (end + start) / 2;
    int comparedValue = strcmp(array[middle], target);

    if (comparedValue == 0)
        return middle;
    else if (comparedValue > 0)
        return searchString(array, target, start, middle - 1);
    else
        return searchString(array, target, middle + 1, end);
}

char *convertInput(int c, char *v[])
{
    char *output = malloc(sizeof(char*));
    output = v[1];

    for (int i = 1; i < c - 1; i++)
    {
        strcat_s(output, sizeof(char*), " ");
        strcat_s(output, sizeof(char*), v[i + 1]);
    }

    return output;
}

int getStringArrayLength(int arrayBitSize, char *strings[])
{
    return arrayBitSize / sizeof(strings[0]);
}