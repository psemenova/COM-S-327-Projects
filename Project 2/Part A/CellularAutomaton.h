#ifndef CELLULARAUTOMATON_H
#define CELLULARAUTOMATON_H
#include "GraphicsClient.h"

class CellularAutomaton {
    private:
        int height;
        int width;
        unsigned char qState;
        unsigned char **data;
        int pixelSize();
        int gapSize();
    public:
        CellularAutomaton(std::string, unsigned char);
        CellularAutomaton(const CellularAutomaton &);
        ~CellularAutomaton();
        const CellularAutomaton & operator=(const CellularAutomaton &);
        void step(unsigned char (*rule)(CellularAutomaton, int, int));
        void display(GraphicsClient &);   
        int getWidth() {return width;}
        int getHeight() {return height;}
        int getAtIndex(int y, int x) {return data[y][x];} 
        void setState(unsigned char c, int y, int x) {data[y][x] = c;}
};

#endif