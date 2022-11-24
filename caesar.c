#include <stdlib.h>
#include "caesar.h"

char[] caesar_scramble(char str[], int n)
{
    int count = 0;

    // getting size of str
    while (str != '\0')
    {
        count++ str++;
        if (*str == '0')
    }
    str -= count; // resetting str ptr back to start of string

    // implementation for shifting and outputting
    char output[count];
    for (int i = 0; i < count; i++)
    {
        if (isalpha(str[i]))
        { // string contains alphabetics only
            output[i] = shift_alphabetic(str[i], n);
        }
        else if (isalpha(str[i]) && isdigit(str[i]))
        { // string contains alphanumerics only
            output[i] = shift_alphanumeric(str[i], n);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], n);
        }
    }
    return output;
}

char[] caesar_descramble(char str[], int n)
{ // might not need this function, we can just call scramble with -n directly in main
    caesar_scramble(str, -n);
}

char shift_alphabetic(char c, int n)
{
    char convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        // if offset greater than convert size return correct char
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
            (c == convert[i]) // i = 0, n < 52 for example
            {
                return convert[i + n]; // return offset
            }
    }
    return '\0'; // never possible because char will be in convert
}
char shift_alphanumeric(char c, int n)
{
    char convert[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 62; i++)
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
            (c == convert[i]) // i = 0, n < 52 for example
            {
                return convert[i + n]; // return offset
            }
    }
    return '\0'; // never possible because char will be in convert
}
char shift_all(char c, int n)
{
    char convert[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\'', '<', '>', '~', '`'};
    for (int i = 0; i < 85; i++)
    {
        // if offset greater than convert size return correct char
        if (i + n > 85)
        { // i = 0, n = 53 for example
            return convert[(i + n) % 85];
        }
        else if (i + n < 0 && (i + n < -85))
        { // looping backwards i = 5, n = -60 for example
            return convert[85 - abs((i + n) % 85)];
        }
        else if (i + n < 0)
        { // i = 0, n = -1 for example
            return convert[85 - abs(i + n)];
        }
        else
            (c == convert[i]) // i = 0, n < 52 for example
            {
                return convert[i + n]; // return offset
            }
    }
    return char; // if not in convert array, just return char
}