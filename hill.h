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

/*Code failing too many times because my determinants are randomly 0
   so making a function to check and if it is by some chance, changing
   my encoding pattern. The function will return 1 if the determinant
   is good to use in calculations and 0 if not.
*/
int determinant_check(int square);

/*Code to generate an encoded matrix: used in three places so for better
   organization and to ensure the determinant of the matrix is not 0.
*/
int *generate_encode(int square);

/*I'm applying some code online at:
    https://www.sanfoundry.com/c-program-find-inverse-matrix/
    that finds the inverse of the generated matrix which is
    when it is necessary to descramble the inputted string.
    The matrix function is equivalent to the main function
    of the online code, and I will be adapting it for my use
    to find the modular multiplicative inverse which is found
    by multiplying the adjugate matrix by the multiplicative
    inverse of the encrypt matrix.
 */

/*These functions are part of the online code but have been modified*/
float determinant(float[][SIZE], float k);
float *cofactor(float[][SIZE], float k);

/*Unused*/
void transpose(float[][SIZE], float[][SIZE], float k);