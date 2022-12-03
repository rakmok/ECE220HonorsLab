#include <stdio.h>
#include "caesar.h"
#include "hill.h"
#include "steg.h"

int main()
{
    // welcome output
    printf("Welcome to the steganography and cipher project!\n");

    int encrypt_or_decrypt = -1;
    printf("Enter 0 if you want to encrypt a string, ");
    printf("enter 1 if you want to decrypt a string, ");
    printf("or enter 2 if you want to decrypt an image.\n");
    while (encrypt_or_decrypt != 0 && encrypt_or_decrypt != 1 && encrypt_or_decrypt != 2)
    {
        scanf("%d", &encrypt_or_decrypt);
        if (encrypt_or_decrypt != 0 && encrypt_or_decrypt != 1 && encrypt_or_decrypt != 2)
        {
            printf("Please enter 0, 1, or 2.\n");
            printf("...\n");
        }
    }
    if (encrypt_or_decrypt == 0)
    { // go into encrypt code
        printf("Please enter a string of no more than 999 characters to encypt.\n");
        printf("Do not include any spaces or a buffer overflow will occur!\n");

        char input_string[1000]; // last char for null terminated string
        scanf("%s", input_string);

        // Decide on Cipher
        int digit;
        char *encrypted;
        if (hill_scramble_boolean(input_string) != 0 && hill_scramble_char(input_string) != 0)
        {
            printf("\nSince your input string can be parsed into a square matrix, it will be encrypted using a hill cipher.\n");
            encrypted = hill_scramble(input_string, hill_scramble_boolean(input_string));
        }
        else
        {
            printf("\nYour input string will be encrypted using a monoalphabetic cipher.\n");
            printf("A key will be outputted after a space at the end of your encrypted string. Save it for later as it will be needed for decryption!\n\n");
            printf("Please enter a digit to shift your input string by.\n");
            scanf("%d", &digit);
            printf("Perfect! Encrypting now.\n.\n.\n.\n");
            encrypted = caesar_scramble(input_string, digit);
        }

        // Ask if user wants back just encrypted string or image with encypted string
        int str_or_image = -1;
        printf("Enter 0 if you want the encrypted string back or\n");
        printf("enter 1 if you want the encrypted image back.\n");
        while (str_or_image != 0 && str_or_image != 1)
        {
            scanf("%d", &str_or_image);
            if (str_or_image != 0 && str_or_image != 1)
            {
                printf("Please enter 0 or 1.\n");
                printf("...\n");
            }
        }

        // Output encrypted string or image
        printf("\n");
        if (str_or_image == 0)
        {
            int i = 0;
            while (encrypted[i] != '\0')
            {
                printf("%c", encrypted[i]);
                i++;
            }
            printf("\n");
        }
        else
        {
            int i = 0;
            while (encrypted[i] != '\0')
            {
                i++;
            }
            steg_stash(encrypted, i); // calling steg_main to do steg implementation
            printf("The image contains your string and is in your repository.\n");
        }

        free(encrypted);
    }
    else if (encrypt_or_decrypt == 1)
    {
        printf("Please enter a string of no more than 999 characters to decrypt.\n");
        printf("Do not include any spaces or a buffer overflow will occur!\n");

        char input_string[1000]; // last char for null terminated string
        scanf("%s", input_string);

        // Decrypt based on cipher used to encrypt
        int digit;
        char *decrypted;
        if (hill_scramble_boolean(input_string) != 0 && hill_scramble_char(input_string) != 0)
        {
            printf("Decrypting now.\n");
            decrypted = hill_descramble(input_string, hill_scramble_boolean(input_string));
        }
        else
        {
            printf("Your input string was encrypted using a monoalphabetic cipher.\nPlease enter the digit you used to shift your input string by when encrypting.\n");
            scanf("%d", &digit);
            decrypted = caesar_descramble(input_string, digit);
            printf("Perfect! Decrypting now.\n.\n.\n.\n");
        }

        // output decrypted string
        int i = 0;
        while (decrypted[i] != '\0')
        {
            printf("%c", decrypted[i]);
            i++;
        }
        printf("\n");

        free(decrypted);
    }
    else
    {
        // steg_remove abstracts the removing of stashed bits and returns encrypted string
        char *encrypted = steg_remove();

        // get string count
        int i = 0;
        while (encrypted[i] != '\0')
        {
            i++;
        }
        char input_string[i + 1];
        input_string[i] = '\0'; // need to put null terminating char at end of input because doesn't transfer from encrypted

        // put encrypted ptr into input_string to be decrypted
        i = 0;
        while (encrypted[i] != '\0')
        {
            input_string[i] = encrypted[i];
            i++;
        }

        // Decrypt based on cipher used to encrypt
        int digit;
        char *decrypted;
        if (hill_scramble_boolean(input_string) != 0)
        {
            printf("Decrypting now.\n");
            decrypted = hill_descramble(input_string, hill_scramble_boolean(input_string));
        }
        else
        {
            printf("Your input string was encrypted using a monoalphabetic cipher.\nPlease enter the digit you used to shift your input string by previously.\n");
            scanf("%d", &digit);
            printf("Perfect! Decrypting now.\n.\n.\n.\n");
            decrypted = caesar_descramble(input_string, digit);
        }

        // output decrypted string
        i = 0;
        while (decrypted[i] != '\0')
        {
            printf("%c", decrypted[i]);
            i++;
        }
        printf("\n");

        free(encrypted);
        free(decrypted);
    }

    return 0;
}
