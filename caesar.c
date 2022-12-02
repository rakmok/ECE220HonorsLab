#include <stdlib.h>
#include "caesar.h"
#include <ctype.h>  //to be able to use isalpha(), isalnum()
#include <string.h> //to be able to use strcpy()

char *caesar_scramble(char str[], int n)
{
    int count = 0;

    // getting size of str
    int k = 0;
    while (str[k] != '\0')
    {
        count++, k++;
    }

    // implementation for shifting and outputting
    char output[count + 3]; // extra locations for tab, the key, and null terminating char
    char key = '2';         // default key is 2 (represents shifting by string which contains everything as opposed to only alphabetics/alphanums)

    // we can combine the following couple lines with the for loop below, but want the user to have a key in order to decrypt string later
    if (parse_string_alph(str, count - 1) == 1)
    { // count - 1 so parsing function doesn't include null terminating character in check
        key = '0';
    }
    else if (parse_string_alnum(str, count - 1) == 1)
    { // count - 1 so parsing function doesn't include null terminating character in check
        key = '1';
    }

    for (int i = 0; i < count; i++)
    { // encryting all chars in string based on ONE of the three methods below
        if (key == '0')
        { // string contains alphabetics only
            output[i] = shift_alphabetic(str[i], n);
        }
        else if (key == '1')
        { // string contains alphanumerics only
            output[i] = shift_alphanumeric(str[i], n);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], n);
        }
    }
    output[count] = ' ';                                          // setting space character to differentiate encrypted string from key
    output[count + 1] = key;                                      // adding key in output which abstracts which of the three methods below is used to encrypt the string
    output[count + 2] = '\0';                                     // manually setting terminated null char
    char *encrypted = (char *)malloc((count + 3) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(encrypted, output);                                    // copying result array onto heap with size count + 3 to include space, key, and null character

    return encrypted;
}

int parse_string_alph(char str[], int count)
{
    // base case 1: if count = 0 reached, meaning only alphabetics in string so return 1
    if (count == -1)
    {
        return 1;
    }
    // base case 2: if a non-alphabetic char found, return 0
    if (isalpha(str[count]) == 0)
    {
        return 0;
    }
    // recursive case: decrease count
    parse_string_alph(str, count - 1);

    return 1; // should never reach here, just for compiler happiness
}

int parse_string_alnum(char str[], int count)
{
    // base case 1: if count = 0 reached, meaning only alphanums in string so return 1
    if (count == -1)
    {
        return 1;
    }
    // base case 2: if a non-alphanum char found, return 0
    if (isalnum(str[count]) == 0)
    {
        return 0;
    }
    // recursive case: decrease count
    parse_string_alnum(str, count - 1);

    return 1; // should never reach here, just for compiler happiness
}

char *caesar_descramble(char str[], int n)
{ // to shift encrypted string back to original based on inputted key
    int count = 1;

    // getting size of str
    int k = 0;
    while (str[k] != '\0')
    {
        count++, k++;
    }

    // getting original key
    char key = '3';
    printf("For the last piece of information, please enter the single digit key that was outputted after your encrypted string.\n");
    scanf("%c", &key);
    while (key != '0' && key != '1' && key != '2')
    {
        scanf("%c", &key);
        if (key != '0' && key != '1' && key != '2')
        {
            printf("Please enter the correct single digit key.\n");
            printf("...\n");
        }
    }

    char output[count + 1]; // extra location for null terminating char
    for (int i = 0; i < count; i++)
    { // encryting all chars in string based on ONE of the three methods below
        if (key == '0')
        { // string contains alphabetics only
            output[i] = shift_alphabetic(str[i], -1 * n);
        }
        else if (key == '1')
        { // string contains alphanumerics only
            output[i] = shift_alphanumeric(str[i], -1 * n);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], -1 * n);
        }
    }
    output[count] = '\0';

    char *decrypted = (char *)malloc((count + 1) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(decrypted, output);                                    // copying result array onto heap with size count + 1 to include null character

    return decrypted;
}

char shift_alphabetic(char c, int n)
{
    char convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // if offset greater than convert size return back to index 0 and decrease offset
            if (i + n > 52)
            { // i = 0, n = 53 for example
                return convert[(i + n) % 52];
            }
            else if (i + n < 0 && (i + n < -52))
            { // looping backwards i = 5, n = -60 for example
                return convert[52 - abs((i + n) % 52)];
            }
            else if (i + n < 0)
            { // i = 0, n = -1 for example
                return convert[52 - abs(i + n)];
            }
            else
            {                          // i = 0, n < 52 for example
                return convert[i + n]; // return offset
            }
        }
    }
    return '\0'; // never possible because char will be in convert
}
char shift_alphanumeric(char c, int n)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 62; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // if offset greater than convert size return correct char
            if (i + n > 62)
            { // i = 0, n = 53 for example
                return convert[(i + n) % 62];
            }
            else if (i + n < 0 && (i + n < -62))
            { // looping backwards i = 5, n = -60 for example
                return convert[62 - abs((i + n) % 62)];
            }
            else if (i + n < 0)
            { // i = 0, n = -1 for example
                return convert[62 - abs(i + n)];
            }
            else
            {                          // i = 0, n < 52 for example
                return convert[i + n]; // return offset
            }
        }
    }
    return '\0'; // never possible because char will be in convert
}
char shift_all(char c, int n)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    for (int i = 0; i < 87; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {

            // if offset greater than convert size return correct char
            if (i + n > 87)
            { // i = 0, n = 53 for example
                return convert[(i + n) % 87];
            }
            else if (i + n < 0 && (i + n < -87))
            { // looping backwards i = 5, n = -60 for example
                return convert[87 - abs((i + n) % 87)];
            }
            else if (i + n < 0)
            { // i = 0, n = -1 for example
                return convert[87 - abs(i + n)];
            }
            else
            {                          // i = 0, n < 52 for example
                return convert[i + n]; // return offset
            }
        }
    }
    return c; // if not in convert array, just return char
}