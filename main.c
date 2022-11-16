#include <stdio.h>
#include "caesar.h"
#include "hill.h"
#include "steg.h"

int main()
{
    printf("Welcome to the steganography and cipher project!\n");
    printf("Please enter a string to encypt.\n");

    // creating file to store user inputted string
    FILE *inFile = fopen("encrypt.txt", "w");
    if (inFile == NULL)
    {
        printf("You do not have PHP access to create new file");
    }

    fclose(inFile);
    return 1;
}
