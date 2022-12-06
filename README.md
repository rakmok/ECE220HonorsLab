# ECE220HonorsLab

Cipher and Steganography Project for ECE 220 Honors Lab

In this codebase, there is a main.c and three other source and header files that link to main:

-The caesar file will implement a monoalphabetic caesar shift based on an inputted integer  
-The hill file will use an generated nxn matrix to multiply with sections of the inputted string  
-The steg file will link to the image file and stash the bits of the scambled text into the least significant bit of each byte in the image.

Just want to emphasize that I am using some code that is not my own!
More information in hill.h, but I need to find the determinant and cofactor of a matrix, so
I am using code from:
https://www.sanfoundry.com/c-program-find-inverse-matrix/  
(The code has been adapted of course as I don't use the main or transpose function, and have added some extra components to cofactor).
