#include "hill.h"
#include "math.h"
#include <string.h>
#define SIZE 99

int hill_scramble_boolean(char str[])
{
    /*Getting the size of the string*/
    int count = 0, s = 0;
    while (str[s] != '\0')
    {
        count++;
        s++;
    }

    /*elaborate way of checking if count is a square up to 99^2*/
    int i, j;
    int is_square = 0; // boolean checker
    for (i = 1; i < SIZE + 1; i++)
    {
        for (j = 1; j < SIZE + 1; j++)

        {
            if (i == j)
            {
                if (count == i * j)
                {
                    is_square = i;
                    break;
                }
            }
        }
        if (is_square != 0)
        {
            break; // want to get out of nested for with two breaks
        }
    }

    /*can't implement hill if not a sqaure matrix*/
    return is_square; // returns 0 if not square or nonzero square dimensions if square
}

char *hill_scramble(char str[], int square)
{
    /*Getting the size of the string*/
    int count = 0, s = 0;
    while (str[s] != '\0')
    {
        count++;
        s++;
    }

    /*creating the encoded matrix and input matrix*/
    char convert[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};
    int encode[count], input[count];

    int i = 0, j;
    for (i = 0; i < count; i++)
    {
        encode[i] = count + i % square; // my encoding pattern

        j = 0;
        while (j < 64)
        { // iterate through convert str
            if (str[i] == convert[j])
            {                 // if input string char matches convert str alphanumeric..
                input[i] = j; // set corresponding index of found char into input
                break;        // only one matching instance so once found exit for next input str char
            }
            j++; // using j and not str because I don't want to put it back to original addr again
        }
    }

    /*multiplying input string by encoded matrix to get scrambled string*/
    i = 0, j = 0;
    int output[count];
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            output[i] = 0;
            int k = 0;
            for (k = 0; k < square; k++)
            {
                output[i * square + j] = input[i * square + k] * encode[k * square + j];
                // 2d matrix syntax would be result[i][j] = input[i][k]*encode[k][j]
            }
        }
    }

    // output array filled with ints that represnt chars; convert ints back to chars based on convert array
    char encryptedChar[count];
    for (i = 0; i < count; i++)
    {
        encryptedChar[i] = convert[output[i]];
    }

    char *encrypted = (char *)malloc(count * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(encrypted, encryptedChar);                       // copying result array onto heap

    return encrypted;
}
char *hill_descramble(char str[])
{
    int count = 4;
    char output[1000] = "To be written";
    char *decrypted = (char *)malloc(count * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(decrypted, output);                              // copying result array onto heap

    return decrypted;
}
void matrix(int n)
{
    float a[SIZE][SIZE];
    float k = n;

    float d = determinant(a, k);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(a, k);
}
/*For calculating Determinant of the Matrix */
float determinant(float a[SIZE][SIZE], float k)
{
    float s = 1, det = 0, b[SIZE][SIZE];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}

void cofactor(float num[SIZE][SIZE], float f)
{
    float b[SIZE][SIZE], fac[SIZE][SIZE];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[SIZE][SIZE], float fac[SIZE][SIZE], float r)
{
    int i, j;
    float b[SIZE][SIZE], inverse[SIZE][SIZE], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    printf("\n\n\nThe inverse of matrix is : \n");

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n");
    }
}