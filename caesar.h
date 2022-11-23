#include <stdio.h>
#include <stdlib.h>

/*The functions below are as their name implies and
    they both take in a string and int argument; the
    string to scramble/de-scramble and the int to
    shift to the next character by that amount.*/
char[] caesar_scramble(char str[], int n);
char[] caesar_descramble(char str[], int n);

/*The helper functions below are called based on the
    type of character in the input string. For example,
    if the input string is BHJhueBlhjkJK, then the
    above functions will only call shift_alphabetic.*/
char shift_alphabetic(char c, int n);
char shift_alphanumeric(char c, int n);
char shift_all(char c, int n);
