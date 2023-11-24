#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringArrayLength(int arrayBitSize, char *strings[]);
char *convertInput(int c, char *v[]);

int main(int argc, char *argv[])
{
    char *userInput = convertInput(argc, argv);
    printf("%s\n", userInput);

    char *monopolyOptions[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    int arrayLength = getStringArrayLength(sizeof(monopolyOptions), monopolyOptions);

    for (int i = 0; i < arrayLength; i++)
        if(strcmp(monopolyOptions[i], userInput) == 0)
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
        strcat_s(output, sizeof(char*), " ");
        strcat_s(output, sizeof(char*), v[i + 1]);
    }

    return output;
}

int getStringArrayLength(int arrayBitSize, char *strings[])
{
    return arrayBitSize / sizeof(strings[0]);
}