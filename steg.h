#include <stdio.h>
#include <stdlib.h>

/*This function does all of the main steg I/O like asking if the user wants to use a default image
 *  or their own image, and stashes the bits
 */
void steg_stash(char *encrypted, int count);

/*Lines 60-62 adapted from a thread in StackOverflow: https://stackoverflow.com/questions/41384262/convert-string-to-binary-in-c. */

/*This function de-stashes the bits that were previously stashed, turns them back into chars, and return them to be decrypted*/
char *steg_remove();
