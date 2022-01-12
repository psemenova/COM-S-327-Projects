# COM S 327 - Project 1 Part C

## Features Implemented
Created 3 of the following functions:
- initCA
- create1DCA
- create2DCA
- set1DCACell
- set2DCACell
- displayCA
- step1DCA
- step2DCA
- main
- rule

This program creates a stucture ca_data which contains an 2d array pointer, width and height of the 2d array, a qState, a flag, and the number of states.

Takes in input from the command line to create the structure.

Prints an error message if the input is incorrect.

Reads file input and uses those values for each index in the 2d array

Changes the array with the rule function and prints the output after the user hits enter to keep going

## How to Execute Program
1. Make sure that `ca.c`, `ca.h`, `main.c` & `Makefile` are in folder
2. Type `make` into the command line and hit enter
3. Type `./gol` with parameters after it such as `./gol 2 testfile.txt`
4. The parameters are `dimention filename`
5. Hit enter again. This will compile the program and produce an output.
6. To continue onto the next step, hit enter
7. To exit the program press any character and hit enter