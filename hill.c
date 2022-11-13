#include "hill.h"
#include "math.h"
#define SIZE 99

int scramble(char str[])
{
    /*Getting the size of the string*/
    int count = 0;
    while (str != '\0')
    {
        count++;
        str++;
    }
    str = str - count; // putting string ptr back to original address

    /*elaborate way of checking if count is a square up to 99^2*/
    int i, j;
    int is_square = 0; // boolean checker
    int square;        // if is_sqaure == 1, what count the square of
    for (i = 1; i < SIZE + 1; i++)
    {
        for (j = 1; j < SIZE + 1; j++)
            ;
        {
            if (j == i)
            {
                if (count == i * j)
                {
                    is_square = 1;
                    square = i;
                }
            }
        }
    }
    /*can't implement hill if not a sqaure matrix*/
    if (is_square == 0)
    {
        return is_square; // return out if not square
    }

    /*creating the encoded matrix and input matrix*/
    char convert[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};
    int encode[count], input[count];

    i = 0;
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
}
int descramble(char str[])
{
}
void matrix(char c[][], int n)
{
    float a[SIZE][SIZE];
    float k = n;
    int i, j;

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