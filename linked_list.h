#ifndef SparseMatrix_h
#define SparseMatrix_h
#include <stdlib.h>
#include <stdbool.h>
typedef struct Item {
    int row;
    int col;
    double value;
    bool Error;
    char formula[256]; 

    struct Item *next;
} Item;
typedef struct findCell{
    int row;
    int col;
}findCell;
Item * createNode(int r, int c, double val,char* f,bool b); 
void addItem(Item ** head, int r, int c, double val, char* f,bool b); 
void removeItem(Item ** head, int r, int c);
void printItem(Item * head);
double getValue(Item *head, int r, int c);
void freeList(Item * head);
#endif