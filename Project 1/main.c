#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ca.h"

/** 
 * Function: rule
 * 
 * Any live cell with two or three live neighbours survives.
 * Any dead cell with three live neighbours becomes a live cell.
 * All other live cells die in the next generation. Similarly, all other dead cells stay dead.
 * 
 * @params data a pointer to a ca_data structrue
 * @params x the x index of the current poisition
 * @params y the y index of the current position
 * @params flag the wrap flag 
 */
 unsigned char rule(struct ca_data *data, int x, int y) {
    int liveCellCount = 0;
    if(data->flag == 0) {
        int rightX = x + 1, middleX = x, leftX = x - 1;
        int topY = y - 1, middleY = y, bottomY = y + 1;

        if(x == 0) leftX = data->width - 1;
        if (y == 0) topY = data->height - 1; 

        if(x == data->width - 1) rightX = 0;
        if(y == data->height - 1) bottomY = 0;

        if(data->cadata[leftX][topY] == 1) liveCellCount++;
        if(data->cadata[middleX][topY] == 1) liveCellCount++;
        if(data->cadata[rightX][topY] == 1) liveCellCount++;

        if(data->cadata[leftX][middleY] == 1) liveCellCount++;
        if(data->cadata[rightX][middleY] == 1) liveCellCount++;

        if(data->cadata[leftX][bottomY] == 1) liveCellCount++;
        if(data->cadata[middleX][bottomY] == 1) liveCellCount++;
        if(data->cadata[rightX][bottomY] == 1) liveCellCount++;

        if(data->cadata[x][y] == 1 && (liveCellCount == 2 || liveCellCount == 3)) return 1;
        if(data->cadata[x][y] == 0 && liveCellCount == 3) return 1;
        return 0;
    }
    return 0;
}


/**
 * Function: main
 * 
 * takes in 2 parameters from the command line
 * gives an error if the parameters are wrong
 * reads in a file input and initializes a 2DCA
 * with width and height input from the file
 * as well as all of the index inputs 
 * waits for the user to press enter to take
 * a step in the DCA, on any other character input
 * the program exists
 *
 */
int main(int argc, char *argv[]) {

    int initialState = 0;
    char *filepath;
    int dimention;
    int width, height;
    struct ca_data *data;

    if(argc == 3) {
        sscanf(argv[1], "%d", &dimention);

        if(dimention == 1) {
            printf("Error! Wrong Dimentions\n"); 
            exit(-1);
        }
        filepath = argv[2];

        FILE *in_file  = fopen(filepath, "r");
        if (in_file == NULL) {   
            printf("Error! Could not open file\n"); 
            exit(-1);
        } 

        fscanf(in_file, "%d %d", &width, &height);  

        if(dimention == 1) {
            data = create1DCA(width, initialState);
        } else {
            data = create2DCA(width, height, initialState);
        }

        for(int i = 0; i < data->width; i++) {
            for(int j = 0; j < data->height; j++) {
                fscanf(in_file, "%d", &initialState);  
                set2DCACell(data, i, j, initialState);
            }
        }
        
        displayCA(data);
        printf("\n");



        char c;
        while (1){
		    c=fgetc(stdin);
            if(c ==0x0A) {
                step2DCA(data, &rule);
                displayCA(data);
                printf("\n");
                continue;
            } else {
                break;
            }
            c=getchar();
        }
        

    } else {
        printf("Wrong amount of arguments");
    }
    
    return 0;
}