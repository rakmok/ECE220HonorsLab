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

    int encrypt_or_decrypt = 0;
    for (int i = 0; i < count; i++)
    { // encryting all chars in string based on ONE of the three methods below
        if (key == '0')
        { // string contains alphabetics only
            output[i] = shift_alphabetic(str[i], n, encrypt_or_decrypt);
        }
        else if (key == '1')
        { // string contains alphanumerics only
            output[i] = shift_alphanumeric(str[i], n, encrypt_or_decrypt);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], n, encrypt_or_decrypt);
        }
    }
    output[count] = ' ';                                          // setting space character to differentiate encrypted string from key
    output[count + 1] = key;                                      // adding key in output which abstracts which of the three methods below is used to encrypt the string
    output[count + 2] = '\0';                                     // manually setting terminated null char
    char *encrypted = (char *)malloc((count + 3) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    if (encrypted == NULL)
    {
        printf("Not enough space on heap to stash encrypted string.\n");
    }
    strncpy(encrypted, output, count + 3); // copying result array onto heap with size count + 3 to include space, key, and null character

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

    int encrypt_or_decrypt = 1;
    char output[count + 1]; // extra location for null terminating char
    for (int i = 0; i < count; i++)
    { // encryting all chars in string based on ONE of the three methods below
        if (key == '0')
        { // string contains alphabetics only
            output[i] = shift_alphabetic(str[i], -1 * n, encrypt_or_decrypt);
        }
        else if (key == '1')
        { // string contains alphanumerics only
            output[i] = shift_alphanumeric(str[i], -1 * n, encrypt_or_decrypt);
        }
        else
        { // string contains everything else
            output[i] = shift_all(str[i], -1 * n, encrypt_or_decrypt);
        }
    }
    output[count] = '\0';

    char *decrypted = (char *)malloc((count + 1) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    if (decrypted == NULL)
    {
        printf("Not enough space on heap to stash encrypted string.\n");
    }
    strcpy(decrypted, output); // copying result array onto heap with size count + 1 to include null character

    return decrypted;
}

int shift_alphabetic_position(char c, int n)
{
    char convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // if offset greater than convert size return correct int
            if ((i + n > 52) && ((i + n) % 52 != 0))
            { // range from 53 to +infinity BUT i + n is NOT a multiple of +52 (i = 0, n = 88 for example)
                return (i + n) % 52;
            }
            else if ((i + n < 0) && (i + n > -52))
            { // range from -1 to -51 (looping backwards i = 5, n = -6 for example)
                return 52 - abs(i + n);
            }
            else if ((i + n < -52) && ((i + n) % 52 != 0))
            { // range from -53 to -infinity BUT i + n is NOT a multiple of -52 (i = 0, n = -1000 for example)
                return 52 - abs((i + n) % 52);
            }
            else if ((i + n == 52) || (i + n == -52) || ((i + n) % 52 == 0))
            { // range of +52, -52, or a multiple of +/- 52 (for example i = 27, n = 25)
                return 0;
            }
            else
            { // range from 0 to 51 (i = 0, n < 52 for example)
                return i + n;
            }
        }
    }
    return 0; // never possible because char will be in convert
}
char shift_alphabetic(char c, int n, int encrypt_or_decrypt)
{
    char convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // extreme case where i + n % 52 == 0 in encrypt but when program makes n -> -n, i + n % 52 != 0 in decrypt or vice versa
            // for example: i = 4, n = 100 as 4+100 = 104 % 52 = 0 but 4-100 % 52 != 0
            if ((encrypt_or_decrypt == 1) && ((i - n) % 52 == 0) && ((i + n) % 52 != 0) && (shift_alphabetic_position(c, n) == i))
            { // encrypt i + n is a factor of 52 but decrypt is not == 0)
                return convert[n % 52];
            }
            /*else if (encrypt_or_decrypt == 1)
            { // encrypt i + n is not a factor of 52 but decrypt is (might not ever reach here but just in case)
                if ((i - n > 52) && ((i - n) % 52 != 0))
                { // range from 53 to +infinity BUT i + n is NOT a multiple of +52 (i = 0, n = 88 for example)
                    return convert[(i - n) % 52];
                }
                else if ((i - n < 0) && (i - n > -52))
                { // range from -1 to - 51 (looping backwards i = 5, n = -30 for example)
                    return convert[52 - abs(i - n)];
                }
                else if ((i - n < -52) && ((i - n) % 52 != 0))
                { // range from -53 to -infinity BUT i + n is NOT a multiple of -52 (i = 0, n = -1000 for example)
                    return convert[52 - abs((i - n) % 52)];
                }
                else
                { // range from 0 to 51 (i = 0, n < 52 for example)
                    return convert[i - n];
                }
            }*/

            // if offset greater than convert size return correct char
            if ((i + n > 52) && ((i + n) % 52 != 0))
            { // range from 53 to +infinity BUT i + n is NOT a multiple of +52 (i = 0, n = 88 for example)
                return convert[(i + n) % 52];
            }
            else if ((i + n < 0) && (i + n > -52))
            { // range from -1 to -51 (looping backwards i = 5, n = -6 for example)
                return convert[52 - abs(i + n)];
            }
            else if ((i + n < -52) && ((i + n) % 52 != 0))
            { // range from -53 to -infinity BUT i + n is NOT a multiple of -52 (i = 0, n = -1000 for example)
                return convert[52 - abs((i + n) % 52)];
            }
            else if ((i + n == 52) || (i + n == -52) || ((i + n) % 52 == 0))
            { // range of +52, -52, or a multiple of +/- 52 (for example i = 27, n = 25)
                return convert[0];
            }
            else
            { // range from 0 to 51 (i = 0, n < 52 for example)
                return convert[i + n];
            }
        }
    }
    return '\0'; // never possible because char will be in convert
}

int shift_alphanumeric_position(char c, int n)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 62; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // if offset greater than convert size return correct int
            if ((i + n > 62) && ((i + n) % 62 != 0))
            { // range from 63 to +infinity BUT i + n is NOT a multiple of +62 (i = 0, n = 900 for example)
                return (i + n) % 62;
            }
            else if ((i + n < 0) && (i + n > -62))
            { // range from -1 to -61 (looping backwards i = 5, n = -60 for example)
                return 62 - abs(i + n);
            }
            else if ((i + n < -62) && ((i + n) % 62 != 0))
            { // range from -63 to -infinity BUT i + n is NOT a multiple of -62 (i = 0, n = -1000 for example)
                return 62 - abs((i + n) % 62);
            }
            else if ((i + n == 62) || (i + n == -62) || ((i + n) % 62 == 0))
            { // range of +62, -62, or a multiple of +/- 62 (for example i = 2, n = 60)
                return 0;
            }
            else
            { // range from 0 to 61 (i = 0, n < 52 for example)
                return i + n;
            }
        }
    }
    return 0;
}
char shift_alphanumeric(char c, int n, int encrypt_or_decrypt)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 62; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // extreme case where i + n % 62 == 0 in encrypt but when program makes n -> -n, i + n % 62 != 0 in decrypt or vice versa
            // for example: i = 24, n = 100 as 24+100 = 124 % 62 = 0 but 24-100 % 62 != 0
            if ((encrypt_or_decrypt == 1) && ((i - n) % 62 == 0) && ((i + n) % 52 != 0) && (shift_alphanumeric_position(c, n) == i))
            { // encrypt i + n is a factor of 62 but decrypt is not == 0)
                return convert[n % 62];
            }
            /*else
            { // encrypt i + n is not a factor of 52 but decrypt is (might not ever reach here but just in case)
                if ((i - n > 62) && ((i - n) % 62 != 0))
                { // range from 63 to +infinity BUT i + n is NOT a multiple of +62 (i = 0, n = 88 for example)
                    return convert[(i - n) % 62];
                }
                else if ((i - n < 0) && (i - n > -62))
                { // range from -1 to - 51 (looping backwards i = 5, n = -30 for example)
                    return convert[62 - abs(i - n)];
                }
                else if ((i - n < -62) && ((i - n) % 62 != 0))
                { // range from -63 to -infinity BUT i + n is NOT a multiple of -62 (i = 0, n = -1000 for example)
                    return convert[62 - abs((i - n) % 62)];
                }
                else
                { // range from 0 to 61 (i = 0, n < 52 for example)
                    return convert[i - n];
                }
            }*/

            // if offset greater than convert size return correct char
            if ((i + n > 62) && ((i + n) % 62 != 0))
            { // range from 63 to +infinity BUT i + n is NOT a multiple of +62 (i = 0, n = 900 for example)
                return convert[(i + n) % 62];
            }
            else if ((i + n < 0) && (i + n > -62))
            { // range from -1 to -61 (looping backwards i = 5, n = -60 for example)
                return convert[62 - abs(i + n)];
            }
            else if ((i + n < -62) && ((i + n) % 62 != 0))
            { // range from -63 to -infinity BUT i + n is NOT a multiple of -62 (i = 0, n = -1000 for example)
                return convert[62 - abs((i + n) % 62)];
            }
            else if ((i + n == 62) || (i + n == -62) || ((i + n) % 62 == 0))
            { // range of +62, -62, or a multiple of +/- 62 (for example i = 2, n = 60)
                return convert[0];
            }
            else
            { // range from 0 to 61 (i = 0, n < 52 for example)
                return convert[i + n];
            }
        }
    }
    return '\0'; // never possible because char will be in convert
}

int shift_all_position(char c, int n)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    for (int i = 0; i < 87; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {
            // if offset greater than convert size return correct char
            if ((i + n > 87) && ((i + n) % 87 != 0))
            { // range from 88 to +infinity BUT i + n is NOT a multiple of +87 (i = 0, n = 88 for example)
                return (i + n) % 87;
            }
            else if ((i + n < 0) && (i + n > -87))
            { // range from -1 to - 86 (looping backwards i = 5, n = -60 for example)
                return 87 - abs(i + n);
            }
            else if ((i + n < -87) && ((i + n) % 87 != 0))
            { // range from -88 to -infinity BUT i + n is NOT a multiple of -87 (i = 0, n = -1000 for example)
                return 87 - abs((i + n) % 87);
            }
            else if ((i + n == 87) || (i + n == -87) || (i + n % 87 == 0))
            { // range of +87, -87, or a multiple of +/- 87 (for example i = 27, n = 60)
                return 0;
            }
            else
            { // range from 0 to 86 (i = 0, n < 87 for example)
                return i + n;
            }
        }
    }
    return 0;
}
char shift_all(char c, int n, int encrypt_or_decrypt)
{
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    for (int i = 0; i < 87; i++)
    {
        if (c == convert[i]) // if char inputted matches convert array
        {

            // extreme case where i + n % 87 == 0 in encrypt but when program makes n -> -n, i + n % 87 != 0 in decrypt or vice versa
            // for example: i = 74, n = 100 as 74+100 = 174 % 87 = 0 but 74-100 % 87 != 0
            if ((encrypt_or_decrypt == 1) && ((i - n) % 87 == 0) && ((i + n) % 87 != 0) && (shift_all_position(c, n) == i))
            { // encrypt i + n is a factor of 87 but decrypt is not == 0)
                return convert[n % 87];
            }
            /*else
            { // encrypt i + n is not a factor of 52 but decrypt is (might not ever reach here but just in case)
                if ((i - n > 87) && ((i - n) % 87 != 0))
                { // range from 88 to +infinity BUT i + n is NOT a multiple of +87 (i = 0, n = 88 for example)
                    return convert[(i - n) % 87];
                }
                else if ((i - n < 0) && (i - n > -87))
                { // range from -1 to - 86 (looping backwards i = 5, n = -30 for example)
                    return convert[87 - abs(i - n)];
                }
                else if ((i - n < -87) && ((i - n) % 87 != 0))
                { // range from -88 to -infinity BUT i + n is NOT a multiple of -87 (i = 0, n = -1000 for example)
                    return convert[87 - abs((i - n) % 87)];
                }
                else
                { // range from 0 to 86 (i = 0, n < 86 for example)
                    return convert[i - n];
                }
            }*/

            // if offset greater than convert size return correct char
            if ((i + n > 87) && ((i + n) % 87 != 0))
            { // range from 88 to +infinity BUT i + n is NOT a multiple of +87 (i = 0, n = 88 for example)
                return convert[(i + n) % 87];
            }
            else if ((i + n < 0) && (i + n > -87))
            { // range from -1 to - 86 (looping backwards i = 5, n = -60 for example)
                return convert[87 - abs(i + n)];
            }
            else if ((i + n < -87) && ((i + n) % 87 != 0))
            { // range from -88 to -infinity BUT i + n is NOT a multiple of -87 (i = 0, n = -1000 for example)
                return convert[87 - abs((i + n) % 87)];
            }
            else if ((i + n == 87) || (i + n == -87) || (i + n % 87 == 0))
            { // range of +87, -87, or a multiple of +/- 87 (for example i = 27, n = 60)
                return convert[0];
            }
            else
            { // range from 0 to 86 (i = 0, n < 87 for example)
                return convert[i + n];
            }
        }
    }
    return c; // if not in convert array, just return char
}