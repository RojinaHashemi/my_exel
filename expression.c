#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "expression.h"
#include "linked_list.h"

void pushOpar(OparStack * o,char c){
    o->top++;
    o->data[o->top] = c;
}
char popOpar(OparStack * o){
   
    char c = o->data[o->top];
    o->top--;
    return c;
}
void pushNumb(NumbStack * s,double numb){
    s->top++;
    s->data[s->top] = numb;
}
double popNumb(NumbStack * s){
    double x = s->data[s->top];
    s->top--;
    return x;
}
char observeOpar(OparStack * op){
    return op->data[op->top];
}
int priority(char oparation){
    if(oparation == '*' || oparation == '/') return 2;
    if (oparation == '+' || oparation == '-') return 1;
    return 0;
}
int calculate(NumbStack *numbs,OparStack * opstack){  
      char op = popOpar(opstack);  
      double b = popNumb(numbs); 
      double a = popNumb(numbs); 
      if(op == '+') pushNumb(numbs, a + b);  
      if(op == '-') pushNumb(numbs, a - b);  
      if(op == '*') pushNumb(numbs, a * b);  
      if(op == '/') {
          if(b == 0) {
              printf("Error: Division by zero\n");
              return -1;
          }
          pushNumb(numbs, a / b);  
      }
      return 0;
}
void pushFunc(FuncStack * s,char funcname[]){
    s->top++;
    int i = 0;
    while(funcname[i] !='\0'){
        s->data[s->top][i] = funcname[i];
        i++;
    }
    s->data[s->top][i] = '\0';
}
char * popFunc(FuncStack * s){
    return s->data[s->top--];

}
char * observeFunc(FuncStack * s){
      return s->data[s->top];
}
bool validation(const char * f ){
     return (bool)!strcmp(f,"sin")   ||
            (bool)!strcmp(f,"cos")   ||
            (bool)!strcmp(f,"tan")   ||
            (bool)!strcmp(f,"sinh")  ||
            (bool)!strcmp(f,"cosh")  ||
            (bool)!strcmp(f,"tanh")  ||
            (bool)!strcmp(f,"exp")   ||
            (bool)!strcmp(f,"log")   ||
            (bool)!strcmp(f,"log10") ||
            (bool)!strcmp(f,"sqrt")  ||
            (bool)!strcmp(f,"pow")   ||
            (bool)!strcmp(f,"abs")   ||
            (bool)!strcmp(f,"cot");
         
}
double applyFunc(const char *func_name, double x) {
    if (strcmp(func_name, "sin") == 0) return sin(x);
    if (strcmp(func_name, "cos") == 0) return cos(x);
    if (strcmp(func_name, "tan") == 0) return tan(x);
    if (strcmp(func_name, "sinh") == 0) return sinh(x);
    if (strcmp(func_name, "cosh") == 0) return cosh(x);
    if (strcmp(func_name, "tanh") == 0) return tanh(x);
    if (strcmp(func_name, "exp") == 0) return exp(x);
    if (strcmp(func_name, "cot") == 0) return 1.0/tan(x);
    if (strcmp(func_name, "log") == 0){
        if(x <= 0){
            printf("Error: log argument can not  be zero\n");
            return NAN;
        }
       return log(x);
    }
    if (strcmp(func_name, "log10") == 0){ 
          if(x <= 0){
         printf("Error: log argument can not  be zero\n");
         return NAN;
        }
        return log10(x);}
    if (strcmp(func_name, "sqrt") == 0) {
        if (x < 0) {
            printf("Error: Square root of negative number\n");
            return NAN;
        }
        return sqrt(x);
    }
      printf("Error: Unknown function '%s'\n", func_name);
      return NAN;
}
 int isDigitChar(char c) { 
    return c >= '0' && c <= '9';
}
int isAlphaChar(char c) { 
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); 
}
int isOperatorChar(char c) {
     return c == '+' || c == '-' || c == '*' || c == '/'; }
    
double evaluate(char expression[], Item *matrix_head) {
    NumbStack num_stack;
    num_stack.top = -1;

    OparStack op_stack;
    op_stack.top = -1;

    FuncStack func_stack;
    func_stack.top = -1;
    int error = 0;
    int i = 0;
    char prev = 0;
    bool matrix_cell = false;
   
    while (expression[i] != '\0') {
        //printf("\n # %c",expression[i]);
        char ch = expression[i];
        if (ch == ' ' || ch == '\t' || ch == '\n')
        { 
            i++;
            continue; 
        }
        if (ch == '-' && (i == 0 || isOperatorChar(prev) || prev == '(' || prev == ',')) {
            pushNumb(&num_stack, 0);
            pushOpar(&op_stack, '-');
            i++;
            prev = '-';
            continue;
        }
        if (isDigitChar(ch) || ch == '.') {
            double value = 0;
            double base = 0.1;
            int point = 0;
            while (isDigitChar(expression[i]) || expression[i] == '.') {
                if (expression[i] == '.') {
                    if (point) 
                    { printf("Error: multiple decimal points\n"); 
                        return NAN; }
                    point = 1;
                } else {
                    if (!point) 
                        value = value * 10 + (expression[i] - '0');
                    else {
                         value += (expression[i] - '0') * base; base *= 0.1; 
                    }
                }
                i++;
            }
            pushNumb(&num_stack, value);
            prev = 'n';
            continue;
        }
        if (isAlphaChar(ch)) {
            char func_name[32];
            int j = 0;
            while (isAlphaChar(expression[i])) func_name[j++] = expression[i++];
            func_name[j] = '\0';

            if (!validation(func_name)) 
            { 
                printf("Error: Unknown function '%s'\n", func_name); 
               return NAN;
            }
            pushFunc(&func_stack, func_name);
            prev = 'f';
            continue;
        }
        if (ch == '(') {
            pushOpar(&op_stack, ch);
            i++;
            prev = '(';
            continue;
        }
        if (ch == ',') {
            while (observeOpar(&op_stack) != '(')
               error = calculate(&num_stack, &op_stack);
               if(error == -1){
                return NAN;
               }
            i++;
            prev = ',';

            if (func_stack.top == -1 || strcmp(observeFunc(&func_stack), "pow") != 0) {
              
                matrix_cell = true; 
            }
            continue;
        }
        if (ch == ')') {
            while (observeOpar(&op_stack) != '('){ 
               error = calculate(&num_stack, &op_stack);}
               if(error == -1){
                return NAN;
               }
            popOpar(&op_stack);
            if (matrix_cell) {
                int col = (int)popNumb(&num_stack);
                int row = (int)popNumb(&num_stack);
               
                if(col < 0 && row < 0){
                    printf("Error : invalid value for argument.");
                    return NAN;
                }
                double found = 0;
                found = getValue(matrix_head, row, col);
                
                pushNumb(&num_stack, found);
                matrix_cell = false;
            }
            if (func_stack.top != -1) {
                char *f = popFunc(&func_stack);
                if (strcmp(f, "pow") == 0) {
                    double exp = popNumb(&num_stack);
                    double base = popNumb(&num_stack);
                    pushNumb(&num_stack, pow(base, exp));
                } else {
                    double x = popNumb(&num_stack);
                    double y = applyFunc(f, x);
                    if(y == NAN){
                        return NAN;
                    }
                    pushNumb(&num_stack, y);
                }
            }
            i++;
            prev = ')';
            continue;
        }
        if (isOperatorChar(ch)) {
            while (op_stack.top != -1 && priority(observeOpar(&op_stack)) >= priority(ch))
               error = calculate(&num_stack, &op_stack);
               if(error == -1){
                return NAN;
               }
            pushOpar(&op_stack, ch);
            i++;
            prev = ch;
            continue;
        }
    } 
    while (op_stack.top!= -1){
         error = calculate(&num_stack, &op_stack);
         if(error == -1){
            return NAN;
            break;
         }
        }

    return popNumb(&num_stack);
}