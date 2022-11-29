#include <stdio.h>
#include <stdlib.h>

/*This function does all of the main steg I/O like asking if the user wants to use a default image
 *  or their own image.
 */
void steg_main(char *encrypted, int count);

/*The code under the comment "converting encrypted string into binary and "stashing" in image" in steg.c
 *  has been adapted from a thread in StackOverflow: https://stackoverflow.com/questions/41384262/convert-string-to-binary-in-c.
 */