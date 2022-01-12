# COM S 327 - Project 2 Part A

## Features Implemented
Created the following functions:
- CellularAutomaton(std::string, unsigned char);
- CellularAutomaton(const CellularAutomaton &);
- ~CellularAutomaton();
- const CellularAutomaton & operator=(const CellularAutomaton &);
- void step(unsigned char (*rule)(CellularAutomaton, int, int));
- void display(GraphicsClient &);   
- int getWidth() {return width;}
- int getHeight() {return height;}
- int getAtIndex(int y, int x) {return data[y][x];} 
- void setState(unsigned char c, int y, int x) {data[y][x] = c;}
- GraphicsClient();
- GraphicsClient(std::string, int); //Constructor
- GraphicsClient(const GraphicsClient &); //Copy Constructor
- ~GraphicsClient(); //Destructor
- const GraphicsClient & operator=(const GraphicsClient &); //operator =
- void setBackgroundColor(int, int, int);
- void setDrawingColor(int, int, int);
- void clear();
- void setPixel(int, int, int, int, int);
- void drawRectangle(int, int, int, int);
- void fillRectangle(int, int, int, int);
- void clearRectangle(int, int, int, int);
- void drawOval(int, int, int, int);
- void fillOval(int, int, int, int);
- void drawLine(int, int, int, int);
- void drawstring(int, int, std::string);
- void repaint();

This program creates a 2d array in the CellularAutomaton class

It reads a file input to set all of the states based on the file

Connects to a graphics server and displays the 2d array on there

The program also iterates through and takes steps for the 2d array displaying it on the server. 

## How to Execute Program
1. Make sure that `GraphicsClient.cpp`, `GraphicsClient.h`, `main.cpp`, `CellularAutomaton.cpp`, `CellularAutomaton.h`, a file (`glider.txt`) & `Makefile` are in folder
2. Type `make` into the command line and hit enter
3. Pull up a second Terminal and type `java -jar GraphicsSever.jar` and hit enter
4. In the second terminal type `./graph glider.txt 2` for the two parameters it is the `filename` and the `qstate`
5. Press enter in the second terminal to see the animation
6. Type any other character and hit enter to stop the program
