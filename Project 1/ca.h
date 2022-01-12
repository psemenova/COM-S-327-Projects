#ifndef CA_H
#define CA_H
struct ca_data {
    unsigned char **cadata;
    unsigned char qState;
    int flag;
    int numStates;
    int width;
    int height;
    int dimention;
};
void initCA(struct ca_data * data, int state);
int set1DCACell(struct ca_data *data, unsigned int x, unsigned char state);
int set2DCACell(struct ca_data *data, unsigned int x, unsigned int y, unsigned char state);
void displayCA(struct ca_data *data);
void step1DCA(struct ca_data *ca, unsigned char (*rule)(struct ca_data *, int x)); 
void step2DCA(struct ca_data *ca, unsigned char (*rule)(struct ca_data *, int x, int y)); 
struct ca_data *create1DCA(int w, unsigned char qstate); 
struct ca_data *create2DCA(int w, int h, unsigned char qstate);
#endif