# COM S 327 - Project 2 Part A

## Key Data Structures Used
    unsigned char arrays
    pointers
    double pointers
    sockets
    for loops
    function pointers

## Source Files Used
    stdio.h
    stdlib.h
    iostream
    string.h
    sys/socket.h
    arpa/inet.h
    unistd.h
    sys/ioctl.h

# Files
## Cellular Automaton
This file has the creation of the Cellular Automaton structure that is displayed on the graphics server. 

This class contains many methods for the creation of the object, like copy constructors, destructors, = operators and etc. 

It also contains methods to manipulate the cells in the 2d array, to set them all to zero, or change and individual cell or initialize them in a specific way. 

This is also where the display method comes in to play that brings the graphics client and the cellular automaton together. 

## Graphics Client
Has methods that send information to the server of what drawings they want showed. The varous drawRectangle, drawOval, drawstring and etc., play a key role in the visual side of the server. 

Some of the other fuctions like getMouseClick and getFile play an imporant role in the functionaliy of the program, they read in input from the server of where the mouse click happens and parse it into x and y coordinates that are then interpereted based on where the buttons are draw on the screen. 