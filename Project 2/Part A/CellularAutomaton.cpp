#include <string>
#include <iostream>
#include "CellularAutomaton.h"
#include "GraphicsClient.h"
using namespace std;

/**
 * @brief Construct a new Cellular Automaton:: Cellular Automaton object
 * 
 * Creates a CellularAutomaton with a 2d array whose states
 * are read in from a file input
 * 
 * @param fileName name of the file that contains the 2d Array
 * @param state the qstate
 */
CellularAutomaton::CellularAutomaton(std::string fileName, unsigned char state) {
    qState = state;
    int initState;

    FILE *in_file  = fopen(fileName.c_str(), "r");
    if (in_file == NULL) {   
        cout << "Error! Could not open file" << endl; 
        exit(-1);
    } 

    fscanf(in_file, "%d %d", &height, &width);

    data = (unsigned char **) malloc(height * sizeof(unsigned char *));
    if(data == NULL) {
        cout << "Error initializing data structure array" << endl;
        exit(-1);
    }
	for(int i = 0; i < height; i++) {
		data[i] = (unsigned char *) malloc(width * sizeof(unsigned char));
        if(data[i] == NULL) {
            cout << ("Error initializing data structure array");
            exit(-1);
        }
    }

    data[0][0] = 0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            fscanf(in_file, "%d", &initState);  
            this->setState(initState, i, j);
        }
    }
}

/**
 * @brief Construct a new Cellular Automaton:: Cellular Automaton object
 * 
 * copy constructor: creates a new object copying over the values from
 * an existing object 
 * @param rhs the object to copy from 
 */
CellularAutomaton::CellularAutomaton(const CellularAutomaton &rhs) {
    height = rhs.height;
    width = rhs.width;
    qState = rhs.qState;

    data = (unsigned char **) malloc(height * sizeof(unsigned char *));
    if(data == NULL) {
        printf("Error initializing data structure array");
        exit(-1);
    }
	for(int i = 0; i < height; i++) {
		data[i] = (unsigned char *) malloc(width * sizeof(unsigned char));
        if(data[i] == NULL) {
            printf("Error initializing data structure array");
            exit(-1);
        }
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            data[i][j] = rhs.data[i][j];
        }
    }
}

/**
 * @brief Destroy the Cellular Automaton:: Cellular Automaton object
 * the destructor
 * deletes allocated data from the object
 * 
 */
CellularAutomaton::~CellularAutomaton() {
    for (int i = 0; i < height; i++){
        delete data[i];
    }
    delete data; 
}

/**
 * @brief 
 * deletes the previously initialized object
 * and copies the data from the passed in object 
 * @param rhs the object to copy the data from
 * @return const CellularAutomaton& 
 */
const CellularAutomaton &CellularAutomaton::operator=(const CellularAutomaton &rhs){
    if(this != &rhs) {
        height = rhs.height;
        width = rhs.width;
        qState = rhs.qState;

        for (int i = 0; i < height; i++){
            delete data[i];
        }
        delete data;

        data = (unsigned char **) malloc(height * sizeof(unsigned char *));
        if(data == NULL) {
            printf("Error initializing data structure array");
            exit(-1);
        }
	    for(int i = 0; i < height; i++) {
		    data[i] = (unsigned char *) malloc(width * sizeof(unsigned char));
            if(data[i] == NULL) {
                printf("Error initializing data structure array");
                exit(-1);
            }
        }

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                data[i][j] = rhs.data[i][j];
            }
        }
    }

    return *this;
}

/**
 * @brief 
 * takes in a rule for moving through the 2d array
 * goes through each index and changes it based on the rule
 * @param rule 
 */
void CellularAutomaton::step(unsigned char (*rule)(CellularAutomaton ca, int x, int y)) {
    CellularAutomaton * temp = new CellularAutomaton(*this);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            data[i][j] = rule(*temp, i, j);
        }   
    }
}


/**
 * @brief 
 * takes in a graphics object and displayes the 2d array
 * on the server
 * @param object 
 */
void CellularAutomaton::display(GraphicsClient &object) {
    object.clear();
    object.setDrawingColor(3, 207, 252);

    for (int i = 0; i < height; i++ ) {
        for (int j = 0; j < width; j++) {
            if(data[i][j] == 1) {
                object.fillRectangle(
                    (j * pixelSize()) + (j * gapSize()),
                    (i * pixelSize()) + (i * gapSize()),
                    pixelSize(),
                    pixelSize()
                );
            }
        }
        
    }

    object.repaint();
}

/**
 * @brief 
 * private method for manipulating the pixel size
 * @return int 
 */
int CellularAutomaton::pixelSize() {
    int m = max(height, width); 
    if(m > 200 && m <= 600) return 1;
    if(m > 150 & m <= 200) return 2;
    if(m > 50 & m <= 100) return 4;
    if(m > 1 & m <= 50) return 10;
    cout << "Error in size" << endl;
    return 0;
}
/**
 * @brief 
 * private method for manipulating the gap size
 * @return int 
 */
int CellularAutomaton::gapSize(){
    int m = max(height, width); 
    if(m > 200 && m <= 600) return 0;
    if(m > 150 & m <= 200) return 1;
    if(m > 50 & m <= 100) return 1;
    if(m > 1 & m <= 50) return 2;
    cout << "Error in size" << endl;
    return 0;
}