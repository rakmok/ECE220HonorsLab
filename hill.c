#include "hill.h"
#include "math.h"
#include <string.h>
#define SIZE 99
#define defined_det 4

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

    /*can't implement hill if not a square matrix*/
    return is_square; // returns 0 if not square or nonzero square dimensions if square
}

int hill_scramble_char(char str[])
{
    /*Getting the size of the string*/
    int count = 0, s = 0;
    while (str[s] != '\0')
    {
        count++;
        s++;
    }

    /*checking to see if inputted string chars are all in convert array*/
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    int i = 0, j, is_valid;
    for (i = 0; i < count; i++)
    {
        j = 0, is_valid = 0;
        while (j < 87)
        { // iterate through convert str
            if (str[i] == convert[j])
            { // if input string char matches convert str alphanumeric, set is_valid to true
                is_valid = 1;
            }
            j++; // using j and not str because I don't want to put it back to original addr again
        }
        if (is_valid == 0)
        { // if even one char in input string doesn't match convert, hill can't work
            return is_valid;
        }
    }
    return is_valid; // returns 0 if input string can't be encrypted using hill, 1 if it can
}

char *hill_scramble(char str[], int square)
{
    int count = square * square;

    /*creating the encoded matrix and input matrix*/
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    int input[count];

    int i = 0, j;
    for (i = 0; i < count; i++)
    {
        j = 0;
        while (j < 87)
        { // iterate through convert str
            if (str[i] == convert[j])
            {                 // if input string char matches convert str alphanumeric..
                input[i] = j; // set corresponding index of found char into input
                break;        // only one matching instance so once found exit for next input str char
            }
            j++; // using j and not str because I don't want to put it back to original addr again
        }
    }

    // generating encode based on string size
    int *encode = generate_encode(square);

    if (determinant_check(square) == 0)
    { // if det is 0, can't descramble later, use new encoding pattern
        for (i = 0; i < count; i++)
        {
            encode[i] = (i * i); // failsafe encoding pattern
        }
    }

    /*multiplying input string by encoded matrix to get scrambled message (still all ints)*/
    i = 0, j = 0;
    int output[count];
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            int k = 0, add = 0;
            for (k = 0; k < square; k++)
            {
                add += input[i * square + k] * encode[k * square + j];
                // 2d matrix syntax would be result[i][j] = input[i][k]*encode[k][j]
            }
            output[i * square + j] = add;
        }
    }

    // output array filled with ints that represent chars; convert ints back to chars based on convert array
    char encryptedChar[count + 1];
    for (i = 0; i < count; i++)
    { // all value have to be mod even if they are < 87 or the logic won't work
        encryptedChar[i] = convert[output[i] % 87];
    }
    encryptedChar[count] = '\0';                                  // manually adding terminating null char
    char *encrypted = (char *)malloc((count + 1) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(encrypted, encryptedChar);                             // copying result array onto heap including count + 1 for null character

    free(encode);
    return encrypted;
}
char *hill_descramble(char str[], int square)
{
    int count = square * square;

    /*creating the input matrix based on the encrypted string as well as the encoded matrix to get the inverse of it later*/
    char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', ':', ';', ',', '.', '?', '/', '\\', '<', '>', '~', '`'};
    int encode_inverse[count], input[count];

    int i = 0, j;
    for (i = 0; i < count; i++)
    {
        j = 0;
        while (j < 87)
        { // iterate through convert str
            if (str[i] == convert[j])
            {                 // if input string char matches convert str alphanumeric..
                input[i] = j; // set corresponding index of found char into input
                break;        // only one matching instance so once found exit for next input str char
            }
            j++; // using j and not str because I don't want to put it back to original addr again
        }
    }

    // generating encode based on string size
    int *encode = generate_encode(square);

    /* getting the adjugate of the encode matrix */
    float temp[SIZE][SIZE];
    float *adjugate_matrix;
    i = 0, j = 0;
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            temp[i][j] = encode[(i * square) + j]; // cofactor uses 2d matrix so converting
        }
    }
    float square_float = (float)square;
    adjugate_matrix = cofactor(temp, square_float);

    /*getting the modular multiplicative inverse of the encode matrix by multiplying the adjugate matrix by the multiplicative inverse*/
    int mult_inverse = -1;
    i = 1;
    int det = determinant(temp, square_float), det_mod;
    if (det > 0)
    { // code for finding mod of a number (% doesn't work with negatives as -40%87 returns -40 but I want it to return 47)
        det_mod = (det % 87);
    }
    else
    {
        det_mod = det;
        while (det_mod < 0)
        {
            det_mod += 87;
        }
    }
    while (mult_inverse == -1)
    {
        if (((det_mod * i) % 87) == 1)
        {
            mult_inverse = i;
            break;
        }
        i++;
    }
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            // need to mod the adjugate matrix before multiplying by multiplicative inverse
            if (adjugate_matrix[(i * square) + j] > 0)
            { // code for finding mod of a number (% doesn't work with negatives as -40%87 returns -40 but I want it to return 47)
                adjugate_matrix[(i * square) + j] = (int)adjugate_matrix[(i * square) + j] % 87;
            }
            else
            {
                while (adjugate_matrix[(i * square) + j] < 0)
                {
                    adjugate_matrix[(i * square) + j] += 87;
                }
            }

            encode_inverse[(i * square) + j] = adjugate_matrix[(i * square) + j] * mult_inverse;

            // need to mod again after multiplying by mult_inverse
            if (encode_inverse[(i * square) + j] > 0)
            { // code for finding mod of a number (% doesn't work with negatives as -40%87 returns -40 but I want it to return 47)
                encode_inverse[(i * square) + j] = (encode_inverse[(i * square) + j] % 87);
            }
            else
            {
                while (encode_inverse[(i * square) + j] < 0)
                {
                    encode_inverse[(i * square) + j] += 87;
                }
            }
        }
    }
    /*multiplying input matrix (all ints) by modular multiplicative inverse of encode matrix to get unscrambled message (still all ints)*/
    i = 0, j = 0;
    int output[count];
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            int k = 0, add = 0;
            for (k = 0; k < square; k++)
            {
                add += input[i * square + k] * encode_inverse[k * square + j];
                // 2d matrix syntax would be result[i][j] = input[i][k]*encode_inverse[k][j]
            }
            output[i * square + j] = add;
        }
    }

    /* turn output ints into chars (which will be displayed on console as decrypted message) */
    char output_char[count + 1];
    output_char[count] = '\0';
    for (i = 0; i < count; i++)
    { // all value have to be mod even if they are < 87 or the logic won't work
        output_char[i] = convert[output[i] % 87];
    }

    char *decrypted = (char *)malloc((count + 1) * sizeof(char)); // dynamically allocating memory so not lost when returning to main
    strcpy(decrypted, output_char);                               // copying result array onto heap including + 1 for null character

    free(encode);
    return decrypted;
}

/*void matrix(int n)
{
    float a[SIZE][SIZE];
    float k = n;

    float d = determinant(a, k);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(a, k);
}*/
// For calculating Determinant of the Matrix
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

float *cofactor(float num[SIZE][SIZE], float f)
{
    int square = (int)f;
    float *adjugate_matrix = (float *)malloc((square * square * sizeof(float)));
    if (f == 1)
    {
        adjugate_matrix[0] = 1;
        return adjugate_matrix;
    }

    // code to get cofactor of matrix
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
    // transpose(num, fac, f);

    // turning adjugate 2d into 1d matrix to be used in hill_descramble
    i = 0, j = 0;
    for (i = 0; i < f; i++)
    {
        for (j = 0; j < f; j++)
        {
            adjugate_matrix[(i * square) + j] = fac[j][i]; // doing fac[j][i] instead of [i][j] because that is how to get transpose
        }
    }
    return adjugate_matrix;
}
/*Finding transpose of matrix
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
}*/
int determinant_check(int square)
{
    float temp[SIZE][SIZE];
    int *encode; // size count

    // generating encode based on string size
    encode = generate_encode(square);

    // turning encode from 1d to 2d
    int i, j;
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            temp[i][j] = encode[(i * square) + j]; // cofactor uses 2d matrix so converting
        }
    }

    float square_float = (float)square;
    if (determinant(temp, square_float) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    free(encode);
}
int *generate_encode(int square)
{
    int *encode = (int *)malloc(square * square * sizeof(int));

    // generating encode based on string size
    int i = 0, j = 0;
    for (i = 0; i < square; i++)
    {
        for (j = 0; j < square; j++)
        {
            if (i == 0)
            {
                encode[(i * square) + j] = defined_det; // defined_det is macro that allows me to change what det of encode is
            }
            else if (i == j)
            {
                encode[(i * square) + j] = 2;
            }
            else
            {
                encode[(i * square) + j] = 1;
            }
        }
    }

    return encode;
}