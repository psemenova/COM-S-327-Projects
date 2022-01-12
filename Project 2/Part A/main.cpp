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

int main(int argc, char **argv) {
    
    std::string filename;
    int qstate;
    int PORT_NUMBER = 7777;
    std::string URL = "127.0.0.1";

    if(argc == 3) {
        filename = argv[1];
        sscanf(argv[2], "%d", &qstate);

        GraphicsClient *x = new GraphicsClient(URL, PORT_NUMBER);
        CellularAutomaton ca(filename, qstate);
    
        x->setBackgroundColor(90, 80, 99);
        x->clear();
        x->repaint();
        ca.display(*x);
        
        char c;
        while (1){
		    c=fgetc(stdin);
            if(c ==0x0A) {
                ca.step(&rule);
                ca.display(*x);
                continue;
            } else {
                break;
            }
            c=getchar();
        }

    } else {
        cout << "Wrong number of command line arguments" << endl;
        exit(-1);
    }

    
}
