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

## Function Descroption
# Cellular Automaton
- CellularAutomaton(std::string, unsigned char);
    - Constructor
    - Creates a 2d array in the object filling in the indexes with values that are read in from a file
- CellularAutomaton(const CellularAutomaton &);
    - Copy constructor
    - creates a new object with the variables copied over from the old one
- ~CellularAutomaton();
    - Destructor
- CellularAutomaton & operator=(const CellularAutomaton &)
    - if the two objects are not equal, copies over the variables form the old object into the current
- step(unsigned char (*rule)(CellularAutomaton, int, int))
    - iterates over the values int the 2d array and chagnes them according to the rule
- display
    - displays the 2d array on the graphics server 
- getWidth
    - gets the width of the object
- getHeight
    - gets the height of the object
- getAtIndex
    - gets the value at the index of the object
- setState
    - sets the value at the index of the object
# Graphics Client
- GraphicsClient(std::string, int);
    - Constructor 
    - creates a connection to the server
- GraphicsClient(const GraphicsClient &); 
    - Copy Constructor
    - creates a connection to the server from the existing connection
- ~GraphicsClient();
    - Destructor
    - stops the connection
- const GraphicsClient & operator=(const GraphicsClient &); 
    - stops the connection to the server and creates a new one from the passed in object
- setBackgroundColor(int, int, int)
    - sets the background to the passed in color
- setDrawingColor(int, int, int)
    - sets the drawing color to the passed in color
- clear()
    - clears everything to the background color
- setPixel(int, int, int, int, int)
    - sets the pixel at a specific coordinate to the passed in color
- drawRectangle(int, int, int, int)
    - draws a rectangle outline of the given parameters at the given location
- fillRectangle(int, int, int, int);
    - does the same thing as the draw rectangle but fills it in with the color
- clearRectangle(int, int, int, int)
    - clears (sets the pixels to the background color) at the location and size specified by the parameters. 
- drawOval(int, int, int, int)
    - does the same thing as the draw rectangle but instead draws an oval
- fillOval(int, int, int, int)
    - same as the fill rectangle but instead it does an oval
- drawLine(int, int, int, int)
    - draws a line from point 1 to point 2
- drawstring(int, int, std::string)
    - draws the given string at the given position
- repaint(
    - send the redraw (repaint) signal to the attached graphics server