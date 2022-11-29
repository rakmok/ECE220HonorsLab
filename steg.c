#include "steg.h"
#include <string.h>

void steg_main(char *encrypted, int count)
{
    // Ask if user has an image to stash bits in or wants to use a default image (that program provides)
    int ownImage_or_defaultImage = -1;
    printf("Enter 0 if you have your own image or\n");
    printf("enter 1 if you want to use the default image.\n");
    while (ownImage_or_defaultImage == -1)
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

    // converting encrypted string into binary and "stashing" in image
    char *binary = (char *)malloc(8 * count * sizeof(char) + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for (int i = 0; i < count; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (encrypted[i] & (1 << j))
            {
                strcat(binary, "1");
            }
            else
            {
                strcat(binary, "0");
            }
        }
    }

    free(binary);
    fclose(inFile);
}