#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "GraphicsClient.h"
#include "CellularAutomaton.h"

using namespace std;

/**
 * @brief 
 * The Game of Life Rule implemented
 * to interate the cells and change them to a certain value
 * @param ca the Cellular Automaton
 * @param y coordinate
 * @param x coorcinate
 * @return unsigned char 
 */
unsigned char rule(CellularAutomaton ca, int y, int x) {
    int liveCellCount = 0;
    int rightX = x + 1, middleX = x, leftX = x - 1;
    int topY = y - 1, middleY = y, bottomY = y + 1;

    if(x == 0) leftX = ca.getWidth() - 1;
    if(y == 0) topY = ca.getHeight() - 1; 

    if(x == ca.getWidth() - 1) rightX = 0;
    if(y == ca.getHeight() - 1) bottomY = 0;

    if(ca.getAtIndex(topY, leftX) == 1) liveCellCount++;
    if(ca.getAtIndex(topY, middleX) == 1) liveCellCount++;
    if(ca.getAtIndex(topY, rightX) == 1) liveCellCount++;

    if(ca.getAtIndex(middleY, leftX) == 1) liveCellCount++;
    if(ca.getAtIndex(middleY, rightX) == 1) liveCellCount++;

    if(ca.getAtIndex(bottomY, leftX) == 1) liveCellCount++;
    if(ca.getAtIndex(bottomY, middleX) == 1) liveCellCount++;
    if(ca.getAtIndex(bottomY, rightX) == 1) liveCellCount++;

    if(ca.getAtIndex(y, x) == 1 && (liveCellCount == 2 || liveCellCount == 3)) return 1;
    if(ca.getAtIndex(y, x) == 0 && liveCellCount == 3) return 1;
    return 0;
}

/**
 * @brief 
 * draws the side panel with all the various buttons
 * @param x Graphics Client object
 */
void drawButtons(GraphicsClient *x) {
    //Draw Side Panel
    x->setDrawingColor(0,0,0);
    x->fillRectangle(600, 0, 200, 600);
    x->setDrawingColor(90, 80, 99);
    x->fillRectangle(610, 10, 180, 580);
    x->repaint();

    int buttonX = 630;
    int wordX = 650;
    int buttonY= 30;
    int wordY = 45;

    int buttonWidth = 140;
    int buttonHeight = 30;

    //Draw Step
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY, "Step");
    //Draw Run
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 50, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 50, "Run");
    //Draw Pause
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 100, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 100, "Pause");
    //Draw Reset
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 150, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 150, "Reset");
    //Draw Random
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 200, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 200, "Random");
    //Draw Load
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 250, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 250, "Load");
    //Draw Quit
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 300, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 300, "Quit");
    //Draw Clear
    x->setDrawingColor(0,0,0);
    x->fillRectangle(buttonX, buttonY + 350, buttonWidth, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 350, "Clear");

    //Select size (1,2,3)
     x->setDrawingColor(0,0,0);
    x->drawstring(wordX, wordY + 420, "Select Size");
    x->fillRectangle(buttonX, buttonY + 450, buttonWidth / 3, buttonHeight);
    x->fillRectangle(buttonX + 47, buttonY + 450, buttonWidth / 3, buttonHeight);
    x->fillRectangle(buttonX + 94, buttonY + 450, buttonWidth / 3, buttonHeight);
    x->setDrawingColor(255,255,255);
    x->drawstring(wordX, wordY + 450, "1");
    x->drawstring(wordX + 40, wordY + 450, "2");
    x->drawstring(wordX + 80, wordY + 450, "3");

    x->repaint();
}



/**
 * @brief Main Funcion
 * 
 * connects to the server 
 * draws a Cellular Automaton on the screen
 * the varous buttons do specidic things 
 * STEP: moves the 2d array to the next iteration
 * RUN: starts the animation for the 2d array
 * PAUSE: pauses the program 
 * RANDOM: Creates a random 2d array with the cells randomly set to 1 or 0
 * LOAD: Loads in a file from the computer to display 
 * QUIT: stops the program
 * RESET: sets the 2d array back to the uploaded file
 * CLEAR: clears the screan
 * SET SIZE 1, 2, 3: sets the size of the cellular Automaton to 40x40, 150x150, 600x600
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) {
    
    std::string filename = "";
    int qstate = 0;
    int PORT_NUMBER = 7777;
    std::string URL = "127.0.0.1";
    int xCoord; 
    int yCoord;

    if(argc == 1) {

        GraphicsClient *x = new GraphicsClient(URL, PORT_NUMBER);
        CellularAutomaton ca("glider.txt", 0);
    
        x->setBackgroundColor(90, 80, 99);
        x->clear();
        x->repaint();
        
        drawButtons(x);
        ca.display(*x);

        int count = 0;
        int paused = 1;  // 0 == false, anything else == true 
        int mouseInput; 
         while(1) {
            usleep(110000);
            mouseInput = x->getMouseClick(&yCoord, &xCoord, ca.getHeight(), ca.getWidth());
            if(mouseInput == 2) { // RUN
                paused = 0;
            } else if (mouseInput == 3) { // PAUSE
                paused = 1; 
            } else if (mouseInput == 1) { // STEP
                ca.step(&rule);
                x->clearRectangle(0,0, 600, 600);
                ca.display(*x);
            } else if (mouseInput == 4) { // RESET
                x->clearRectangle(0,0, 600, 600);
                if(filename != "") {
                    ca = CellularAutomaton (filename, qstate);
                    ca.display(*x);
                }
                ca.display(*x);
            } else if (mouseInput == 5) { // RANDOM
                int tempSize = ca.getHeight();
                ca = CellularAutomaton (tempSize, -1); // change size
                x->clearRectangle(0,0, 600, 600);
                ca.display(*x);
            } else if (mouseInput == 6) { // LOAD
                x->getFile();
                filename = x->getFileName();
                while(filename == "") {
                    filename = x->getFileName();
                }
                cout << filename << endl;
                x->clearRectangle(0,0, 600, 600);
                ca = CellularAutomaton(filename, 0);
                ca.display(*x);
            } else if (mouseInput == 7) { // QUIT
                delete(x);
                return 0;
            } else if (mouseInput == 8) { // CLEAR
                ca.setStatesToZero();
                x->clearRectangle(0,0, 600, 600);
                ca.display(*x);
            } else if (mouseInput == 9) { // SET SIZE 1
                x->clearRectangle(0,0, 600, 600);
                paused = 1;
                ca = CellularAutomaton(40, 0);
                ca.display(*x);
            } else if (mouseInput == 10) { // SET SIZE 2
                paused = 1;
                x->clearRectangle(0,0, 600, 600);
                ca = CellularAutomaton(150, 0);
                ca.display(*x);
            } else if (mouseInput == 11) { // SET SIZE 3
                paused = 1;
                x->clearRectangle(0,0, 600, 600);
                ca = CellularAutomaton(600, 0);
                ca.display(*x);
            } else if (mouseInput == 12) { // SET SINGLE CELL
                if(ca.getAtIndex(yCoord, xCoord) == 0) ca.setAtIndex(yCoord, xCoord, 1);
                else {
                    ca.setAtIndex(yCoord, xCoord, 0);
                    x->clear();
                    drawButtons(x);
                }
                ca.display(*x);
            }
            if(!paused) {
                ca.step(&rule);
                x->clearRectangle(0,0, 600, 600);
                ca.display(*x);
            }

        }


    } else {
        cout << "Wrong number of command line arguments" << endl;
        exit(-1);
    }

    
}