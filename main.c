#include <stdio.h>
#include "caesar.h"
#include "hill.h"
#include "steg.h"

int main()
{
    // welcome output
    printf("Welcome to the steganography and cipher project!\n");
    printf("Please enter a string to encypt.\n");

    char input_string[];
    scanf("%s", &input_string);

    /* creating file to store user inputted string
    FILE *inFile = fopen("encrypt.txt", "w");
    if (inFile == NULL)
    {
        printf("You do not have PHP access to create a new file.\n");
    }

    // copying inputted string to text file
    fprintf(infile, "%s", input_string);
    */

    // Decide on Cipher
    int digit;
    char encypted[];
    if (hill_scramble_boolean != 0)
    {
        printf("Since you're input string can be parsed into a square matrix, it will be encrypted using a hill cipher.\n");
        encypted = hill_scramble(input_string, hill_scramble_boolean);
    }
    else
    {
        printf("Please enter a digit to shift your input string by.\n");
        scanf("%d", &digit);
        encrypted = caesar_scramble(input_string, digit);
    }

    // Ask if user wants back just encrypted string or image with encypted string
    int str_or_image = -1;
    printf("Enter 0 if you want the encrypted string back.\n");
    printf("Enter 1 if you want the encrypted image back.\n");
    while (str_or_image == -1)
    {
        scanf("%d", &str_or_image);
        if (str_or_image != 0 && str_or_image != 1)
        {
            printf("Please enter 0 or 1.\n");
        }
    }

    // Output encrypted string or image
    if (str_or_image == 0)
    {
        printf("%d", encrypted);
    }
    else
    {
        printf("The image is in your repository.\n");
    }

    // fclose(inFile);
    return 0;
}
