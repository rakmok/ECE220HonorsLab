#include <stdio.h>
#include <stdlib.h>

/*The functions below are as their name implies and
    they both take in a string and int argument; the
    string to scramble/de-scramble and the int to
    shift to the next character by that amount.
 */
char *caesar_scramble(char str[], int n);
char *caesar_descramble(char str[], int n);

/*Two recursive functions used to parse string and determine if string is composed of all alphabetics,
 *  all alphanumerics, or if it is neither in which case I will use shift_all to encrypt the inputted
 *  string. The functions return 1 if all alphabetics and all alphanumerics respectively, or return 0 otherwise.
 */
int parse_string_alph(char str[], int count);
int parse_string_alnum(char str[], int count);

/*The helper functions below are called based on the
    type of character in the input string. For example,
    if the input string is BHJhueBlhjkJK, then the
    above functions will only call shift_alphabetic.
 */
char shift_alphabetic(char c, int n, int encrypt_or_decrypt);
char shift_alphanumeric(char c, int n, int encrypt_or_decrypt);
char shift_all(char c, int n, int encrypt_or_decrypt);

/*Helper function to return the position of the character in the convert array;
 *  this is used to differentiate between a case where i + n % convert size is 0
 *  for either encrypt or decrypt and when i + n % convert size is not 0 for either
 *  but is 0 for i - n % convert size which is a condition. Realized that the logic
 *  mixes the two up so need to check if the position of the decrypt char is the same
 *  as the position of the encrypt char because that is the key difference.
 */
int shift_alphabetic_position(char c, int n);
int shift_alphanumeric_position(char c, int n);
int shift_all_position(char c, int n);
