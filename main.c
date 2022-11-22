#include <stdio.h>
#include "caesar.h"
#include "hill.h"
#include "steg.h"

int main()
{
    printf("Welcome to the steganography and cipher project!\n");
    printf("Please enter a string to encypt.\n");

    str input_string[];
    scanf("%s", &input_string);

    // creating file to store user inputted string
    FILE *inFile = fopen("encrypt.txt", "w");
    if (inFile == NULL)
    {
        printf("You do not have PHP access to create new file");
    }

    // copying inputted string to text file
    fprintf(infile, "%s", input_string);

    // Decide on Cipher
    int digit;
    if (hill_scramble == 1)
    {
        printf("Since you're input string can be parsed into a square matrix, it will be encrypted using a hill cipher");
        hill_scramble(input_string);
    }
    else
    {
        printf("Please enter a digit to shift your input string by.");
        scanf("%d", &digit);
        caesar_scramble(input_string, digit);
    }

    fclose(inFile);
    return 0;
}
