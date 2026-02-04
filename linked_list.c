#include <stdio.h>
#include <string.h>
#include "linked_list.h"

Item * createNode(int r, int c, double val, char* f,bool b) {
    Item *newitem = (Item*)malloc(sizeof(Item));
    newitem->row = r;
    newitem->col = c;
    newitem->value = val;
    newitem->Error =b;
    int i = 0;
    while(f[i] != '\0') {
        newitem->formula[i] = f[i];
        i++;
    }
    newitem->formula[i] = '\0';
    newitem->next = NULL;
    return newitem;
}

void addItem(Item ** head, int r, int c, double val, char* f,bool b) {
    
    Item * temp = *head;
    Item * prev = NULL;
    while(temp != NULL) {
        if(temp->row == r && temp->col == c) {
            temp->value = val;
            temp->Error = b;
            int i = 0;
            while(f[i] != '\0') {
                temp->formula[i] = f[i];
                i++;
            }
            temp->formula[i] = '\0';
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Item * newspace = createNode(r, c, val, f,b);
    if(prev == NULL)
        *head = newspace;
    else 
        prev->next = newspace;
}

void removeItem(Item ** head, int r, int c) {
    Item * temp = *head;
    Item * prev = NULL;
    while(temp != NULL) {
        if(temp->row == r && temp->col == c) {
            if (prev == NULL) 
                *head = temp->next;
            else
                 prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

double getValue(Item *head, int r, int c) {
    Item *cur = head;
    while(cur != NULL) {
        if(cur->row == r && cur->col == c) 
            return cur->value;
        cur = cur->next;
    }
    return 0;
}

void printItem(Item * head) {
    Item* temp = head;
    printf("\n--- Spreadsheet Status ---\n");
    while(temp != NULL) {
        printf("Cell %d %d: Value=%lf, Formula=%s Error:%d\n", 
            temp->row,
            temp->col , 
            temp->value, 
            temp->formula,
            temp->Error
        );
        temp = temp->next;
    }
}


void freeList(Item * head){
    Item * temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }

}
