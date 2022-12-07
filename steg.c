#include "steg.h"
#include <string.h>
#include <math.h>

#define size_string 11 // soft-coding size of string to be up to 2^11 bits when converted

void steg_stash(char *encrypted, int count)
{
    // Ask if user has an image to stash bits in or wants to use a default image (that program provides)
    int ownImage_or_defaultImage = -1;
    printf("Enter 0 if you have your own image or\n");
    printf("enter 1 if you want to use the default image.\n");
    while (ownImage_or_defaultImage != 0 && ownImage_or_defaultImage != 1)
    {
        scanf("%d", &ownImage_or_defaultImage);
        if (ownImage_or_defaultImage != 0 && ownImage_or_defaultImage != 1)
        {
            printf("Please enter 0 or 1.\n");
        }
    }

    char fileName[1000];
    int image_width;
    int image_height;
    FILE *inFile;
    if (ownImage_or_defaultImage == 0)
    {
        printf("Please enter your image name followed by a space and\n");
        printf("then the image height followed by a space and then the image width\n");
        printf("For example: beach.png 256 256 or sunshine.JPEG 1024 4032.\n");
        sscanf("%s %d %d", fileName, &image_width, &image_height);
        int fileName_check = -1; //-1 if invalid, changes to 1 if valid

        // check if valid file extension
        while (fileName_check == -1)
        {
            // opening user-inputted image to write (for binary)
            inFile = fopen(fileName, "wb");
            if (inFile == NULL)
            {
                printf("Please enter a valid file extension.\n");
                scanf("%s", fileName);
            }
            else
            {
                fileName_check = 1;
            }
        }
    }
    else
    {

        // opening default image to write (for binary)
        inFile = fopen("everest.jpg", "wb");
        if (inFile == NULL)
        {
            printf("You do not have PHP access to open a new file. Check your user permission and try again.\n");
            return;
        }
    }

    // converting encrypted string into binary
    char *binary = (char *)malloc(8 * count * sizeof(char) + size_string); // each char is one byte (8 bits) + size of string data to be stored first
    if (binary == NULL)
    {
        printf("Not enough space on heap to stash encrypted string.\n");
        return;
    }
    int m = size_string; // leaving space for size of string in binary
    int j;
    for (int i = 0; i < count; i++)
    {
        for (j = 7; j >= 0; j--)
        {
            binary[m] = (encrypted[i] >> j) & 1 ? 1 : 0;
            m++;
        }
    }

    // storing size of string (in binary) at beginning of bitmap
    m = 0;
    for (j = size_string - 1; j >= 0; j--)
    {
        binary[m] = (count >> j) & 1 ? 1 : 0;
        m++;
    }

    // stashing encrypted string bits into least significant byte of image
    fprintf(inFile, "\n\n\n"); // first lines hold essential information
    int k = 0;
    while (k < ((count * 8) + size_string))
    {
        fprintf(inFile, "%d", binary[k]);
        k++;
    }

    free(binary);
    fclose(inFile);
}

char *steg_remove()
{
    // Ask if user has their own image or if they used the default image to stash their encrypted string
    int ownImage_or_defaultImage = -1;
    printf("Enter 0 if you used your own image or enter 1 if you\n");
    printf("used the default image to stash your encrypted string.\n");
    while (ownImage_or_defaultImage != 0 && ownImage_or_defaultImage != 1)
    {
        scanf("%d", &ownImage_or_defaultImage);
        if (ownImage_or_defaultImage != 0 && ownImage_or_defaultImage != 1)
        {
            printf("Please enter 0 or 1.\n");
        }
    }
    FILE *inFile;
    if (ownImage_or_defaultImage == 0)
    {
        char fileName[1000];
        inFile = fopen(fileName, "r");
    }
    else
    {
        inFile = fopen("everest.jpg", "r");
    }

    fscanf(inFile, "\n\n\n"); // first lines hold essential information

    // start by removing 11 bits which represent size of encrypted bits from image, changing back to int, and storing in count
    int i;
    int size_binary[size_string];
    for (i = 0; i < size_string; i++)
    {
        size_binary[i] = fscanf(inFile, "%d", size_binary);
    }

    int count = 0, power = 0;
    for (i = size_string - 1; i >= 0; i--)
    { // converting binary to decimal
        if (size_binary[i] == 1)
        {
            count += pow(2, power);
        }
        power++;
    }

    int encrypted_bits[count * 8];
    // getting rest of bits from image based on count and storing in output
    for (i = 0; i < count * 8; i++)
    {
        encrypted_bits[i] = fscanf(inFile, "%d", encrypted_bits);
    }

    // convert binary to char
    char *encrypted = (char *)malloc(count + 1); // dynamically allocating memory for encrypted bits and null terminating char
    encrypted[count] = '\0';                     // manually setting terminated null char

    return encrypted;
}