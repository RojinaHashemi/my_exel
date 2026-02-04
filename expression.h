#ifndef EXP_H 
#define EXP_H

#include "linked_list.h"
#include <stdbool.h>

typedef struct OparStack {
     char data[256];
      int top; 
} OparStack;
typedef struct NumbStack {
     double data[256];
     int top;
} NumbStack;
typedef struct FuncStack { 
    char data[256][15]; 
    int top; 
} FuncStack;

void pushOpar(OparStack * o, char c);
char popOpar(OparStack * o);
char observeOpar(OparStack * op);
void pushNumb(NumbStack * s, double numb);
double popNumb(NumbStack * s);
double observeNumb(NumbStack * s); 
void pushFunc(FuncStack * s, char funcname[]);
char * popFunc(FuncStack * s);
char * observeFunc(FuncStack * s);
int priority(char oparation);
int calculate(NumbStack *numbs, OparStack * opstack);
bool validation(const char * f);
double evaluate(char expression[], Item *head);

#endif