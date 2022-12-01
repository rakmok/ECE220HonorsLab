#include <stdio.h>
#include <stdlib.h>
#define SIZE 99

/*The functions below will create a 2d array based
   on the divisibility of the string and pass that
   to the matrix function to multiply by a
   generated 'matrix' array of the same size;
   the boolean is check if the input string is even
   a square or else program will use caesar instead.
 */

int hill_scramble_boolean(char str[]);
char *hill_scramble(char str[], int square);
char *hill_descramble(char str[], int square);

/*I'm applying some code online at:
    https://www.sanfoundry.com/c-program-find-inverse-matrix/
    that finds the inverse of the generated matrix which is
    when it is necessary to descramble the inputted string.
    The matrix function is equivalent to the main function
    of the online code, and I will be adapting it for my use.
 */
void matrix(int n);

/*These functions are part of the online code */
float determinant(float[][SIZE], float);
void cofactor(float[][SIZE], float);
void transpose(float[][SIZE], float[][SIZE], float);