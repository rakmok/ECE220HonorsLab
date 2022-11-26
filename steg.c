#include "steg.h"

void steg_main()
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

    char fileName[];
    if (ownImage_or_defaultImage == 0)
    {
        printf("Please enter your image name including file type (.png, .JPEG, etc.)\n");
        scanf("%s", fileName);
    }
    else
    {

        // opening image to write (for binary)
        FILE *inFile = fopen("image.PNG", "wb");
        if (inFile == NULL)
        {
            printf("You do not have PHP access to create a new file.\n");
        }
    }
}