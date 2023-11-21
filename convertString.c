#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    This code was made to write my own version of the functions from the C libraries, such as: 
    atoi() - stdlib.h, 
    atof() - stdlib.h,
    pow() - math.h, 
    strcpy_s() - string.h [this last one was not intended to be rewrite my own version, 
    but I couldn't find a way to use the original properly 
    and it's old version 'strcpy()' is unsafe]
*/

/* Main purpuse of the code */
double convertStringToFloat(char *input);
int convertStringToInteger(char *input);

/* Basic exponentiation function that only suports integers for now */
int powerOf(int base, int exponent);

/* Functions to verify users input on terminal */
int verifyCommandLineArgument(int c, char *v[]);
int verifyStringDigit(char *input);
int countCharacters(char *input, char *chars, int start);

/* Function to copy a string to another stack of memory */
char *copyString(char *input);

int main(int argc, char *argv[])
{
    /* Verify command line arguments */
    if (!verifyCommandLineArgument(argc, argv))
        return 1;
    else
        printf("\nTrue\n\n");

    /* Copy original string input to debug code after */
    char *sample = copyString(argv[1]);

    /* Convert string input into a integer */
    float numberValue = convertStringToFloat(argv[1]);

    /* Check results using atof() from stdlib, function that servers the same purpuse as I proposed */
    if (numberValue == atof(sample))
        printf("Success! Printed: %f\n", numberValue);
    else
        printf("Failed... Value returned: %f\n", numberValue);

    /* Free manually allocated memory from the string copy */
    free(sample);
    return 0;
}

double convertStringToFloat(char *input)
{
    double floatNumber = 0;
    double holdDecimalPart = 0;
    if (countCharacters(input, ".", 0) == 0)
    {
        floatNumber += convertStringToInteger(input);
        return floatNumber;
    }

    char beforePoint[sizeof(input)] = "\0";
    char afterPoint[sizeof(input)] = "\0";

    int isPositive = 1;
    if (input[0] == '-')
        isPositive = 0;

    int pointIndex = 0;
    for (int i = 0; i < strlen(input); i++)
        if (input[i] == '.')
            pointIndex = i;

    for (int i = 0; i < pointIndex; i++)
    {
        beforePoint[i] = input[i];
    }

    beforePoint[pointIndex + 1] = '\0';

    pointIndex++;
    for (int i = 0; i < strlen(input); i++)
    {
        afterPoint[i] = input[pointIndex];
        pointIndex++;
    }

    holdDecimalPart += convertStringToInteger(afterPoint);

    if (isPositive)
        floatNumber = convertStringToInteger(beforePoint) + (holdDecimalPart / powerOf(10, strlen(afterPoint)));
    else
        floatNumber = convertStringToInteger(beforePoint) + ((-1) * (holdDecimalPart / powerOf(10, strlen(afterPoint))));

    printf("\nFinal Number: %f\n\n", floatNumber);

    return floatNumber;
}

int convertStringToInteger(char *input)
{
    /* Checks if the number is positive, default value = True */
    int isPositive = 1;

    /* Checks for valid non digit characters */
    if (input[0] == '-' || input[0] == '+')
    {
        /* If negative changes value to False */
        if (input[0] == '-')
            isPositive = 0;

        /* Remove non digit from the start of the array rewriting the entire array without the first element */
        for (int i = 0; i < strlen(input); i++)
        {
            char characterCopy = input[i + 1];
            input[i] = characterCopy;
        }
        /* OBS.: This is the reason why this code needs a string copy to debug, since a string is a pointer to a character 
        even if you modify the string outside of the scope of the function in which you intend to debug it still gets changed globally. */
    }

    /* Variable to hold the return value typed integer */
    int finalNumber = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        /* Sum of the ASCII value of the digit minus it's constant (48) to number times times it's decimal place */
        finalNumber += (input[i] - 48) * powerOf(10, strlen(input) - i - 1);
    }

    /* If the number is a negative integer, returns the value times - 1 to change signs */
    if (!isPositive)
        return finalNumber * (-1);

    /* If number is positive returns value */
    return finalNumber;
}

int powerOf(int base, int exponent)
{
    /* Recursive default case */
    if (exponent == 0)
        return 1;

    /* Recursively multiplies base by itself 'exponent' times */
    return (base * powerOf(base, exponent - 1));
}

int verifyCommandLineArgument(int c, char *v[])
{
    /* If users input has more than one argument other then the file call itself, return error message */
    if (c != 2)
    {
        printf("Usage: ./convert number");
        return 0;
    }

    /* If argument isn't a valid number, return error message */
    if (!verifyStringDigit(v[1]))
    {
        printf("Program only compatible with number inputs.");
        return 0;
    }

    /* If passes everything return true */
    return 1;
}

int verifyStringDigit(char *input)
{
    /* Checks for any non digit character other than a floating point and a number sign */
    if (input[0] != '+' && input[0] != '-' && input[0] != '.' && !isdigit(input[0]))
        return 0;

    /* Counting for floating points in string starting from second element, since the first element was already verified */
    int numberOfFloatingPoints = countCharacters(input, ".", 1);

    if (numberOfFloatingPoints > 2 || numberOfFloatingPoints < 0)
        return 0;

    /* Counts non digit characters through array starting with second element */
    int numberOfNonDigitCharacters = 0;
    for (int i = 1; i < strlen(input); i++)
        if (!isdigit(input[i]))
            numberOfNonDigitCharacters++;
    
    /* If the number of non digits characters is different from the number of floating points return false */
    if (numberOfNonDigitCharacters != numberOfFloatingPoints)
        return 0;

    /* Return true if string passes the tests */
    return 1;
}

int countCharacters(char *input, char *chars, int start)
{
    /* Variable to hold the number of target characters in a determined string */
    int count = 0;

    /* Loop through the string considering starting point */
    for (int i = start; i < strlen(input); i++)
        /* Loop through every target character and count up if equal */
        for (int j = 0; j < strlen(chars); j++)
            if (input[i] == chars[j])
                count++;

    /* Return count */
    return count;
}

char *copyString(char *input)
{
    /* Allocates memory size of the users input */
    char *output = malloc(sizeof(input));
    
    /* Copies every element of the array to another */
    for (int i = 0; i < strlen(input); i++)
        output[i] = input[i];

    /* Returns string from copied variable */
    return output;
}