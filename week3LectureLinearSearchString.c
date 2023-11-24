#include <stdio.h>
#include <stdlib.h>

int getStringArrayLength(int arrayBitSize, char *strings[]);
int compareStrings(char *first, char *second);
int stringLength(char *input);
char *convertInput(int c, char *v[]);
char *concat(char *str1, char *str2);

int main(int argc, char *argv[])
{
    char *userInput = convertInput(argc, argv);

    char *monopolyOptions[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    int arrayLength = getStringArrayLength(sizeof(monopolyOptions), monopolyOptions);

    for (int i = 0; i < arrayLength; i++)
        if(compareStrings(monopolyOptions[i], userInput))
        {
            printf("Found at index: %i\n", i);
            free(userInput);
            return 0;
        }
            
    printf("Not found.\n");
    free(userInput);

    return 0;
}

char *convertInput(int c, char *v[])
{
    char *output = malloc(sizeof(char*));
    output = v[1];

    for (int i = 1; i < c - 1; i++)
    {
        output = concat(output, " ");
        output = concat(output, v[i + 1]);
    }

    return output;
}

char *concat(char *str1, char *str2)
{
    static char output[1024] = "\0";
    for (int i = 0; i < stringLength(str1); i++)
        output[i] = str1[i];

    int j = 0;
    for (int i = stringLength(str1); i < stringLength(str1) + stringLength(str2); i++)
    {
        output[i] = str2[j];
        j++;
    }

    return output;
}

int compareStrings(char *first, char *second)
{
    if (stringLength(first) != stringLength(second))
        return 0;

    int equalCharacters = 0;
    for (int i = 0; i < stringLength(first); i++)
        if (first[i] == second[i])
            equalCharacters++;

    if (equalCharacters == stringLength(first))
        return 1;

    return 0;
}

int stringLength(char *input)
{
    int count = 0;
    for (int i = 0; input[i] != 0; i++)
        count++;

    return count;
}

int getStringArrayLength(int arrayBitSize, char *strings[])
{
    return arrayBitSize / sizeof(strings[0]);
}