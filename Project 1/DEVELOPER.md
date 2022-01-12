# COM S 327 - Project 1 Part C

## Key Data Structures Used
    unsigned char array
    unsigned char pointer to array
    unsigned char pointer to a 2d array
    stuct
    function pointer
    if/else logic
    for loops

## Source Files Used
    stdio.h
    stdlib.h
    time.h

## Function Descroption
- initCA
    - requires two parameters: the `struct ca_data` pointer for the stucture and the `int state` for the array value 
    - depending on the dimention of the ca_data initializes either a 1d or 2d array
    - if input is `-1` sets the indexes to random `0's` and `1's`
- set1DCACell
    - requires three parameters: the `struct ca_data` pointer for the stucture, the `unsigned int x` for the index and the `unsigned char state` for the value to set the array at that index
    - takes in a value and an index and sets the `array[x] = state`
- set2DCACell
    - requires four parameters: the `struct ca_data` pointer for the stucture, the `unsigned int x` for the index, the `unsigned int y` for the second index in the 2d array, and the `unsigned char state` for the value to set the array at that index
    - takes in an index for the 2d array and sets the `array[x][y] = state`
- displayCA
    - requires one parameter: the `struct ca_data` 
    - depending on if it is a 1d array 2d array, prints the output accordingly 
- create1DCA
    - requires two paramters: the `int w` and the `unsigned char qstate`
    - creates a 1d array of length `w` and initializes every index to the `qstate`
- create1DCA
    - requires three paramters: the `int w` for the width, the `int h` for the height and the `unsigned char qstate`
    - creates a 2d array of the given dimmentions 
    - initializes each index to the `qstate` value
- step1DCA
    - requires two parameters: the `struct ca_data` structure, the `unsigned char (*rule)` for the rule to change the values accordinly
    - takes in a structure and a rule and changes all of the indicies of the array based on the rule given
- step2DCA
    - requires two parameters: the `struct ca_data` structure, the `unsigned char (*rule)` for the rule to change the values accordinly
    - takes in a structure and goes through the 2d array and changes all the indices to the values based on the given rule