# ECE220HonorsLab

Cipher and Steganography Project for ECE 220 Honors Lab

In this codebase, there is a main.c and three other source and header files that link to main:

-The caesar file will implement a monoalphabetic caesar shift based on an inputted integer
-The hill file will use an generated nxn matrix to multiply with sections of the inputted string
-The steg file will link to the image file and stash the bits of the scambled text into the least significant bit of each byte in the image.

Just want to emphasize that I am using some code that is not my own!
More information in hill.h, but if I need to find the inverse of a matrix,
I am using code from:
https://www.sanfoundry.com/c-program-find-inverse-matrix/
(I am still deciding whether I need to use it or not because I am multiplying the input string matrix by a predetermined matrix of the same size, but if I use an algorithm to generate the "predetermined" matrix
every time for different string sizes, I will need it or if I know the string size beforehand, I will know the predetermined matrix and thus its inverse).
