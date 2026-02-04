#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "expression.h"
#include "linked_list.h"
/*This function takes an operator character ,and a pointer to operstack  as input and pushes the charcter
    onto operstack.
    It increases o->top by one.
   It returns nothing duo to being a void function.
*/
void pushOper(OparStack * o,char c){
    o->top++;
    o->data[o->top] = c;
}
/*This function takes a pointer to operstack as input,
 and returns the last operation character in operstack.
 It also decreases o->top by one. 
*/
char popOper(OparStack * o){
    char c = o->data[o->top];
    o->top--;
    return c;
}
/*This function takes a pointer to operstack as input,
  and returns the last operation character in operstack.
  It does not change o->top.
  It will be used in order to observe the last operation in operstack.
*/
char observeOper(OparStack * op){
    return op->data[op->top];
}
/*This function takes an opreration character as input,
  and if it is {*,/} returns 2,and if it is {+,-} returns 1.
  it will be used in order to prioritize simple operations in
  evaluation process.
*/
int priority(char oparation){
    if(oparation == '*' || oparation == '/') return 2;
    if (oparation == '+' || oparation == '-') return 1;
    return 0;
}
/*This function takes a double ,and a pointer to numbstack as input,
  and pushes the double onto numbstack.
    It increases s->top by one.
   It returns nothing duo to being a void function.
*/
void pushNumb(NumbStack * s,double numb){
    s->top++;
    s->data[s->top] = numb;
}
/*This function takes a pointer to numbstack as input,
 and returns the last double  in numbstack.
 It also decreases o->top by one. 
*/
double popNumb(NumbStack * s){
    double x = s->data[s->top];
    s->top--;
    return x;
}
/*This function takes a pointer to numbstack , and 
  a poiter to operstack as input.
  It will take the last operation in operstack, and 
  the last two doubles in numbstack,then it will
  recognise the operation and will operate.
  If division by zero is done it will return -1.
  in case everything is fine it will returns 0.
*/
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
/*This function takes a string that includes function name
  ,and a pointer to funcstack  as input,
    and pushes the string onto operstack.
    It increases s->top by one.
   It returns nothing duo to being a void function.
*/
void pushFunc(FuncStack * s,char funcname[]){
    s->top++;
    int i = 0;
    while(funcname[i] !='\0'){
        s->data[s->top][i] = funcname[i];
        i++;
    }
    s->data[s->top][i] = '\0';
}
/*This function takes a pointer to funcstack as input,
 and returns the last string  in funcstack.
 It also decreases s->top by one. 
*/
char * popFunc(FuncStack * s){
    return s->data[s->top--];
/*This function takes a pointer to funcstack as input,
 and returns the last string  in funcstack.
 It does not change  s->top. 
 It will be used in order to observe the last function in funcstack.
*/
}
char * observeFunc(FuncStack * s){
      return s->data[s->top];
}
/*This function takes a char * and compares it
with valid function names and in case they match 
eachother it will return true otherwise will 
return false.
*/
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
/*This function takes a char * and a double
as input,first compares the char * which 
is the function name with the valid existing 
functions and will apply the function onto 
double and retuns it.
in function sqrt in case negetive number is used
function will return NAN.
in function log and log10 in case negetive number is used
function will return NAN.
and at last in case the function is not recognisable 
function will also returns NAN.
*/
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
/*This function takes a string , and the head of the 
link list as input.it will evaluate the string and returns a double as a
value.
*/
double evaluate(char expression[], Item *matrix_head) {
    //creating a NumbStack
    NumbStack num_stack;
    //initializating num_stack.top with "-1",it means num_stack is empty.
    num_stack.top = -1;
    //creating a OperStack
    OparStack op_stack;
    //initializating op_stack.top with "-1",it means op_stack is empty.
    op_stack.top = -1;
    //creating a FuncStack
    FuncStack func_stack;
    //initializating func_stack.top with "-1",it means func_stack is empty.
    func_stack.top = -1;
    //error will be used to track function calculate.
    int error = 0;
    int i = 0;
    //prev will be used to track the last operation that was done.
    char prev = 0;
    //matrix_cell is a flag to undrestand if we have a matrix cell.
    bool matrix_cell = false;

    while (expression[i] != '\0') {
        //for simplising 
        char ch = expression[i];
        //if we had an unwanted space , we will ignore it.
        if (ch == ' ' || ch == '\t' || ch == '\n')
        { 
            i++;
            continue; 
        }
        /*This part is for detecting negetive numbers.
        {-} has to parts in math:1.between 2 numbers like 5-3 
        2.before a number to show negetivity like -2.
        in this part we will identify only {-} that is for showing negetivity.
        in case current character is {-}, and one of the condition below is true 
        we recognize this - as a starter of a negetive number:
        1.i == 0. it means we are at the beggining of expession. so {-} is
        for a negetive number.
        2. isOperatorChar(prev). it means befor this {-} ther was anothor operation,
        so {-} is definitely for a negetive number.
        3.prev == '(' .it is exactly like i == 0. it means we are  at the beggining.
        4.prev == ','.it means we are at the beggining.
        after detecting that {-} is for negetive number, we push 0 to the num_stack,
        and push {-} to op_stack.
        so -x will return to 0-x which is the same.
        */
        if (ch == '-' && (i == 0 || isOperatorChar(prev) || prev == '(' || prev == ',')) {
            pushNumb(&num_stack, 0);
            pushOper(&op_stack, '-');
            i++;
            prev = '-';
            continue;
        }
        /*This part is for detecting numbers.if ch is a digit or 
        is {.} which is for doubles we start building the number.
        */
        if (isDigitChar(ch) || ch == '.') {
            //for final number
            double value = 0;
            //for fractional part
            double base = 0.1;
            //for detecting numbers with fractional part
            int point = 0;
            while (isDigitChar(expression[i]) || expression[i] == '.') {
                /*If ch is {.} it means we have a number with fractional part.
                   if point is already 1 it means we have two {.} in one number,
                   that is an error.
                   but if point is zero we will make it one.
                   if ch is not {.} , then it means ch is a digit.
                   in that case if point is one it means our number is not an 
                   integer.
                   if point is zero it means our number is an integer.
                */
                if (expression[i] == '.') {
                    if (point) 
                    { printf("Error: multiple decimal points\n"); 
                        return NAN; }
                    point = 1;
                } else {
                    if (!point) 
                        value = value * 10 + (expression[i] - '0');
                    else {
                         value += (expression[i] - '0') * base; 
                         base *= 0.1; 
                    }
                }
                i++;
            }
            //we will push the final number.
            pushNumb(&num_stack, value);
            //our previous is a number.
            prev = 'n';
            continue;
        }
        /*This part is for detecting functions, in case we had a alphabet character,
        we put it in a char[] name func_name,then we check if our function is valid with validation function.
        If it was not it is an error.if its valid we push it into func_stack.
        */
        if (isAlphaChar(ch)) {
            char func_name[32];
            int j = 0;
            while (isAlphaChar(expression[i])){
                 func_name[j++] = expression[i++];}
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
        //if ch is {(}, we just push it into op_stack.
        if (ch == '(') {
            pushOper(&op_stack, ch);
            i++;
            prev = '(';
            continue;
        }
        /*In two situations we will see {,} in our expression:
          1.when we refer to a matrix cell .
          2.when we have function pow.
          in both we need firstly calculate until we have{(}.
          If func_stack was empty or the last function was not pow it
          means that we have a matrix cell. so matrix_cell
          will be true.
        */
        if (ch == ',') {
            while (observeOper(&op_stack) != '(')
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
        /*When we have {)},firstly until we have{(} , we have to calculate and 
        then we have to pop {(}.
        */
        if (ch == ')') {
            while (observeOper(&op_stack) != '('){ 
               error = calculate(&num_stack, &op_stack);}
               if(error == -1){
                return NAN;
               }
            popOpar(&op_stack);
            //If we had a matrix cell the last two numbers are row and column.
            if (matrix_cell) {
                int col = (int)popNumb(&num_stack);
                int row = (int)popNumb(&num_stack);
               //column and row can not be negative
                if(col < 0 || row < 0){
                    printf("Error : negative row or column .");
                    return NAN;
                }
                //we will get the wanted value.
                double found = 0;
                found = getValue(matrix_head, row, col);
                //and we will push it to numbstack.
                pushNumb(&num_stack, found);
                matrix_cell = false;
            }
            //If we had {()} and we have no matrix cell then it means we have function.
            if (func_stack.top != -1) {
                //we take the last function.
                char *f = popFunc(&func_stack);
                if (strcmp(f, "pow") == 0) {
                    //if it was pow the last two numbers are exp and base.
                    double exp = popNumb(&num_stack);
                    double base = popNumb(&num_stack);
                    pushNumb(&num_stack, pow(base, exp));
                } else {
                    //if we had other functions we will use function applyfunc.
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
        /*when ch is a simple operator ,while op_stack is not empty and priority
        of the last operator in op_stack is higher than ch ((*,/) are higher than
        (+,-))we will calculate. and when on of this condition]s are 
        not true then we push opertor to op_stack.
         */
        if (isOperatorChar(ch)) {
            while (op_stack.top != -1 && priority(observeOper(&op_stack)) >= priority(ch))
               error = calculate(&num_stack, &op_stack);
               if(error == -1){
                return NAN;
               }
            pushOper(&op_stack, ch);
            i++;
            prev = ch;
            continue;
        }
    } 
    /*Our experssion is now finished. now until op_stack is empty we will 
    calculate. 
    */
    while (op_stack.top!= -1){
         error = calculate(&num_stack, &op_stack);
         if(error == -1){
            return NAN;
            break;
         }
        }
    //at last only one number is remained in num_stack. we will return that.
    return popNumb(&num_stack);
}