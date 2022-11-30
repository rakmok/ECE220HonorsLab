#include "steg.h"
#include <string.h>

#define size_string 11 // soft-coding size of string to be up to 2^11 bits when converted

void steg_main(char *encrypted, int count)
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
    FILE *inFile;
    if (ownImage_or_defaultImage == 0)
    {
        printf("Please enter your image name including file type (beach.png, sunshine.JPEG, etc.)\n");
        scanf("%s", fileName);
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
    int k = 0;
    while (k < count)
    {
        fprintf(inFile, "%d", binary[k]);
        k++;
    }

    free(binary);
    fclose(inFile);
}