# PolynomialArithmetic
Calculates addition, subtraction and multiplication of two polynomials

Introduction:

This program perform arithmetic operations like addition, subtraction and multiplication on pairs of polynomials. Note each polynomial as well as the operations perform on them are displayed in canonical form. Input is taken through command line in the form of a text file namely, input.txt and output is produce in a file namely output.txt.

The input:

Each line(terminated by a newline character) in the file will represent a polynomial.
The line will contain a list of integers, which when taken in pairs will represents the coefficient and exponent of each of the terms in the polynomial.

Example:

-1 0 5 1 20 3 -9 2 -2 1 1 2 -2 3 1 9 -> -1+5x+20x^3-9x^2-2x+x^2-2x^3+x^9
--> x^9+18x^3-8x^2+3x-1
 
Running the Program:

When running the program remember to specify the input file as well as the output file.
For instance, the program can be run through terminal by specifying the following commands.
g++ -std=c++11 Polynomials.cpp
./a.out input.txt output.txt

 
