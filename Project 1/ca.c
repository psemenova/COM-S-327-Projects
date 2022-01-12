#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ca.h"

/**
 * Function: init1DCA
 * 
 * takes in a pointer to a ca_data structure
 * initializes each index of either 1d or 2d array
 * to the state given
 * initialized to random if the state is -1
 *  
 * @params data a pointer to a struct ca_data
 * @params state an integer for the data array values
 */ 
void initCA(struct ca_data * data, int state) {
    srand(time(0));
    data->qState = state == 255 ? 0 : state; 
    if(data->dimention == 1) {
        for(int i = 0; i < data->width; i++) {
            if(state == 255 && state != 0) {
		        unsigned char random = rand() % data->numStates;
                data->cadata[i] = &random;
            } else {
                data->cadata[i] = (unsigned char *) &data->qState;
            }
        }
    } else {
        for (int i = 0; i < data->width; i++) {
            for (int j = 0; j < data->height; j++) {
                if(state == 255 && state != 0) {
                    unsigned char random = rand() % data->numStates;
                    data->cadata[i][j] = random;
                } else {
                    data->cadata[i][j] = data->qState;
                }
            }
        }
    }
}

/**
 * Function: set1DCACell
 * 
 * Takes a struct ca_data pointer
 * sets the arr in the struct at the index
 * to the given char value
 * 
 * @params data a pointer to a struct ca_data
 * @params index an unsigned integer for the index of the array
 * @params value an unsigned char value for the array at the index
 * @return 0 if setting the value was successful, 1 if it wasn't
 */
int set1DCACell(struct ca_data *data, unsigned int x, unsigned char state) {   
    if((x < 0) || (x >= data->width)) {
        return 1;
    }
    data->cadata[x][0] = state;
    return 0;
}

/**
 * Function: set2DCACell
 * 
 * takes in a pointer to a ca_data structure 
 * sets the index at [x][y] to the state given
 * 
 * @params data a pointer to a struct ca_data
 * @params x for the row index of the 2d array
 * @params y for the column index of the 2d array
 * @params state an unisnged char integer valye for the array at [x][y]
 */
int set2DCACell(struct ca_data *data, unsigned int x, unsigned int y, unsigned char state) {
    if((x < 0) || (y < 0) || (x >= data->width) || (y >= data->height)) {
        return 1;
    }
    data->cadata[x][y] = state;
    return 0;
}

/**
 * Function: display1DCA
 * 
 * Takes a struct ca_data pointer
 * prints out the values in the array
 * from the structure
 * 
 * @params data a pointer to a struct ca_data
 */
void displayCA(struct ca_data * data) {
    if(data->dimention == 1){
        for(int i = 0; i < data->width; i++) {
            printf("%u ", (data->cadata[i][0]));
        }
        printf("\n");
    } else {
        for(int i = 0; i < data->width; i++) {
            for(int j = 0; j < data->height; j++){
                printf("%u ", data->cadata[i][j]);
            }
            printf("\n");
        }
        
    }
}


/**
 * Function: create1DCA
 * 
 * Creates a stuct ca_data pointer
 * allocates space in memory for the pointer
 * sets the struct numCells field to the length given
 * creates an array of numCells length 
 * initializes each index to the value initState
 * 
 * @params numCells an unsigned integer for the length of the array
 * @params initState an unsigned char value that each index in the array gets set to
 * @return data the struct ca_data pointer
 */
struct ca_data* create1DCA(int w, unsigned char qstate) {
    struct ca_data *data = malloc(sizeof(struct ca_data));
    if(data == NULL) {
        printf("Error initializing data structure");
        return NULL;
    }
    data->cadata = (unsigned char **) malloc(w * sizeof(int *));
    if(data->cadata == NULL) {
        printf("Error initializing data structure array");
        return NULL;
    }
    for(int i = 0; i < w; i++) {
		data->cadata[i] = (unsigned char *) malloc(sizeof(unsigned char));
        if(data->cadata[i] == NULL) {
            printf("Error initializing data structure array");
            return NULL;
        }
    }

    data->width = w;  
    data->flag = 0;
    data->dimention = 1;
    data->numStates = 2;
    
	initCA(data, qstate);

    return data;
}

/**
 * Function: create2DCA
 * 
 * creates a struct with a 2d array
 * and initializes all of the indexes to the qstate
 * 
 * @params w - width of the 2d array
 * @params h - height of the 2d arra
 * @params qstate - initial state for all the cells in the 2d array
 */
struct ca_data* create2DCA(int w, int h, unsigned char qstate){
    struct ca_data *data = malloc(sizeof(struct ca_data));
    if(data == NULL) {
        printf("Error initializing data structure");
        return NULL;
    }
    data->width = w;
    data->height = h;
    data->flag = 0;
    data->dimention = 2;
    data->numStates = 2;

    data->cadata = (unsigned char **) malloc(w * sizeof(unsigned char *));
    if(data->cadata == NULL) {
        printf("Error initializing data structure array");
        return NULL;
    }
	for(int i = 0; i < w; i++) {
		data->cadata[i] = (unsigned char *) malloc(h * sizeof(unsigned char));
        if(data->cadata[i] == NULL) {
            printf("Error initializing data structure array");
            return NULL;
        }
    }

    initCA(data, qstate);

    return data;
}

/**
 * Funtion: set1DCA
 * 
 * Takes in a stuct ca_data and
 * each time the function is called 
 * it alters every value depending
 * on the rule function
 * 
 * @params data a pointer to a struct ca_data
 * @params pointer to function
 */
void step1DCA(struct ca_data *ca, unsigned char (*rule)(struct ca_data *, int x)) {
    struct ca_data *temp = malloc(sizeof(struct ca_data));
    if(temp == NULL) {
        printf("Error initializing data structure");
        exit(-1);
    }

    temp->width = ca->width;
    temp->height = ca->height;
    temp->flag = ca->flag;
    temp->dimention = ca->dimention;
    temp->numStates = ca->numStates;

    temp->cadata = (unsigned char **) malloc(temp->width * sizeof(unsigned char *));
    if(temp->cadata == NULL) {
        printf("Error initializing data structure array");
        exit(-1);
    }
	for(int i = 0; i < temp->width; i++) {
		temp->cadata[i] = (unsigned char *) malloc(sizeof(unsigned char));
        if(temp->cadata[i] == NULL) {
            printf("Error initializing data structure array");
            exit(-1);
        }
    }

    for(int i = 0; i < ca->width; i++) {
        unsigned char tempVar = rule(temp, i);
        ca->cadata[i][0] = tempVar;
    }

    for(int i = 0; i < temp->width; i++) {
		free(temp->cadata[i]);
    }
    free(temp->cadata);
    free(temp);
}

/**
 * Funtion: set2DCA
 * 
 * Takes in a stuct ca_data and
 * each time the function is called 
 * it alters every value depending
 * on the rule function
 * 
 * @params data a pointer to a struct ca_data
 * @params pointer to function
 */
void step2DCA(struct ca_data *ca, unsigned char (*rule)(struct ca_data *, int x, int y)) {
    struct ca_data *temp = malloc(sizeof(struct ca_data));
    if(temp == NULL) {
        printf("Error initializing data structure");
        exit(-1);
    }
    temp->width = ca->width;
    temp->height = ca->height;
    temp->flag = ca->flag;
    temp->dimention = ca->dimention;
    temp->numStates = ca->numStates;

    temp->cadata = (unsigned char **) malloc(temp->width * sizeof(unsigned char *));
    if(temp->cadata == NULL) {
        printf("Error initializing data structure array");
        exit(-1);
    }
	for(int i = 0; i < temp->width; i++) {
		temp->cadata[i] = (unsigned char *) malloc(temp->height * sizeof(unsigned char));
        if(temp->cadata[i] == NULL) {
            printf("Error initializing data structure array");
            exit(-1);
        }
    }

    for(int i = 0; i < ca->width; i++) {
        for(int j = 0; j < ca->height; j++) {
            unsigned char tempNum = ca->cadata[i][j];
            temp->cadata[i][j] = tempNum;
        }
    }

    for(int i = 0; i < ca->width; i++) {
        for(int j = 0; j < ca->height; j++) {
            ca->cadata[i][j] = rule(temp, i, j);
        }
    }

    for(int i = 0; i < temp->width; i++) {
		free(temp->cadata[i]);
    }
    free(temp->cadata);
    free(temp);
}