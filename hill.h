#include <stdio.h>
#include <stdlib.h>
#define SIZE 99

/*The two functions below are boolean checkers
   to determine if the input string is even
   a square and if the input string has all the
   characters in the convert array or else the
   program won't be able to change the chars to
   ints; if either returns 0 the program will use
   caesar instead of hill.
 */

int hill_scramble_boolean(char str[]);
int hill_scramble_char(char str[]);

/*The functions below will create a 2d array based
   on the divisibility of the string and pass that
   to the matrix function to multiply by a
   generated 'matrix' array of the same size.
 */
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