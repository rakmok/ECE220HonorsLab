#include "caesar.h"

int scramble(char str[], int n)
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
        { // string contains alphanumerics only..
            output[i] = shift_alphanumeric(str[i], n);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], n);
        }
    }
}
int descramble(char str[], int n);

char shift_alphabetic(char c, int n)
{
    char convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        if (c == convert[i])
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
        if (c == convert[i])
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
        if (c == convert[i])
        {
            return convert[i + n]; // return offset
        }
    }
    return char; // if not in convert array, just return char
}