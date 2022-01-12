#ifdef DCA1D_H_
void init1DCA(int numCells, unsigned char *p);
void set1DCACell(unsigned char *p, int index, unsigned char value);
void display1DCA(unsigned char *p, int numCells);
#define DCA1D_H_ //Header guards to deal with double inclusion
#endif