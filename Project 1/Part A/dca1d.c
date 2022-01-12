#include <stdio.h>
#include <stdlib.h>
#include "dca1d.h"

/**
 * Function: init1DCA
 * 
 * @params numCells an integer for the length of the array
 * @params p an unsnged char pointer to the array
 * 
 * takes in a pointer and initioalizes the array to be of length numCells
 * and each value is set to zero
 */
void init1DCA(int numCells, unsigned char *p) {
    for (int i = 0; i < numCells; i++) {
        p[i] = 0;
    } 
    
}

/**
 * Function: set1DCACell
 * 
 * @params p an unsigned char pointer to the array
 * @params index an integer for the specific index in the array
 * @params value an unsinged char value for the array value
 * 
 * take is an array pointer, a index and a value
 * sets the array at the index to the value
 */
void set1DCACell(unsigned char *p, int index, unsigned char value) {   
    if(index >= 0) {
        p[index] = value;
    }
}

/**
 * Function: display1DCA
 * 
 * @params p an unsinged char pointer for the array
 * @params numCells an integer for the length of the array
 * 
 * takes in an array pointer and prints out all the values in the array 
 * that is of length numCells
 */
void display1DCA(unsigned char *p, int numCells) {
    for (int i = 0; i < numCells; i++) {
        printf("%u ", p[i]);
    }
    printf("\n");
}


/**
 * Function: main
 * 
 * creates a 1-dimentional array of length 25
 * sets all of the odd indicies in the array to 1 and all the even to 2
 * displayes the array in one line 
 */
int main() {
    int SIZE = 25;

    unsigned char p [25];
    init1DCA(SIZE, p);

    for (int i = 0; i < SIZE; i++) {
        if(i % 2 == 0) {
            set1DCACell(p, i, 2);
        } else {
            set1DCACell(p, i, 1);
        }
    }
    
    display1DCA(p, SIZE);

    return 0;
}