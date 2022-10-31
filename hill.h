#include <stdio.h>
#include <stdlib.h>

/*The functions below will create a 2d array based
   on the divisibility of the string and pass that
    to the matrix function to multiply by a
    generated 'matrix' array of the same size
 */

int scramble(char str);
int descramble(char str);

/*I'm applying some code online at:
    https://www.sanfoundry.com/c-program-find-inverse-matrix/
    that finds the inverse of the generated matrix which is
    when it is necessary to descramble the inputted string.
    The matrix function is equivalent to the main function
    of the online code, and I will be adapting it for my use.
 */
void matrix(char c[][], int n);

/*These functions are part of the online code */
float determinant(float[][25], float);
void cofactor(float[][25], float);
void transpose(float[][25], float[][25], float);