#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"
#include "expression.h"
#include "file_operation.h"
bool loadFromFile(Item **head,char* fileName) {
    FILE *f = fopen(fileName, "r");
    char* token;
    if(f == NULL)
        return false;
    char line[512];
    int r,c;
    double v;
    char formula[256];
    bool b;
    while(fgets(line,sizeof(line),f)){
       
        token = strtok(line, ";");  // split by semicolon
        char* alltokens[5];
        int i=0;
        while (token != NULL) {
            alltokens[i++] = token;
            if(i >5 ) 
                break;
            token = strtok(NULL, ";");  // get next token
            
        }  
        
        if(i < 5){
            fclose(f);
            printf("\n error tokenizing ...");
            return false;
        }
        
        r = atoi(alltokens[0]);
        c = atoi(alltokens[1]);
        v= atof(alltokens[2]);
        strcpy(formula,alltokens[3]);
        b = atoi(alltokens[4]);
        addItem(head,r,c,v,formula,b);
        
    }
    fclose(f);
    return true;
}


bool saveToFile(Item *head,char* fileName) {
    FILE *f = fopen(fileName, "w");
    if(f==NULL)
        return false;
    Item *temp = head;
    while(temp != NULL) {
        fprintf(f, "%d;%d;%f;%s;%d\n", temp->row, temp->col, temp->value, temp->formula,temp->Error);
        temp = temp->next;
    }
    fclose(f);
    return true;
}