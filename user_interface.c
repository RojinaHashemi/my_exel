#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"
#include "expression.h"
#include "file_operation.h"
#include "settings.h"
Item *head = NULL;
void reevaluateAll();
int main() {
    int menuChoice;
   
    if(!loadFromFile(&head,DATABASE))
        printf("error loading data");
 
    while (1) {
        printItem(head);
        printf("\nMenu:\n1. Add(Update)\n2. Delete\n3. Save\n4. Save and Exit\nChoice: ");
        scanf("%d", &menuChoice);
        getchar(); 
        if (menuChoice == 1) { //add
            while (1) {
                printItem(head);
                int sub;
                printf("\n1. Add with formula (cell reference)\n2. Add numbers\nChoice: ");
                scanf("%d", &sub);
                while(getchar() != '\n');
                if (sub == 1) {   //formula
                    char temp[256];
                    int r, c;
                    bool b = true;
                    printf("Enter row: "); 
                    scanf("%d", &r);
                    while(getchar() != '\n');
                    printf("Enter column: ");
                    scanf("%d", &c);
                    while(getchar() != '\n');
                    printf("Enter formula: ");
                    fgets(temp, 256, stdin);
                    temp[strcspn(temp, "\n")] = '\0'; 
                    double result = evaluate(temp, head);
                    if (result == NAN){
                        b = true;
                    }
                    addItem(&head, r, c, result, temp,b); 
                    reevaluateAll(); 
                    printItem(head);
                    printf("Add another formula?\n1. Yes\n2. No\nChoice: ");
                    scanf("%d", &sub);
                    getchar();
                    if (sub == 2) 
                    break;
                }
                else if (sub == 2) {// simple value
                    char temp[256]; 
                    int r, c;
                    double value;
                    bool b = false;
                    printf("Enter row: "); 
                    scanf("%d", &r);
                    while(getchar() != '\n');
                    printf("Enter column: "); 
                    scanf("%d", &c);
                    while(getchar() != '\n');
                    printf("Enter value: "); 
                    scanf("%lf",&value);
                    addItem(&head, r, c, value, EMPTY_FORMULA,b); 
                    printItem(head);
                    printf("Add another number?\n1. Yes\n2. No\nChoice: ");
                    scanf("%d", &sub);
                    while(getchar() != '\n');
                    if (sub == 2)
                    break;
                }
            }
        }
        else if (menuChoice == 2) {//delete: set to zero
            int c;
            int r;
            printf("Enter row: ");
            scanf("%d", &r);
            while(getchar() != '\n');
            printf("Enter column: ");
            scanf("%d", &c);
            while(getchar() != '\n');
            removeItem(&head,r,c);
            reevaluateAll(); 
             
        }
        else if (menuChoice == 3) { // save
            if(!saveToFile(head,DATABASE))
                printf("\error saving to file... run with sudo");
        }
        else if (menuChoice == 4) { //save and exit
            if(!saveToFile(head,DATABASE))
                printf("\error saving to file... run with sudo");
            freeList(head);
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
void reevaluateAll() {
    Item *tmp = head;
    int reevalCounter =0;
    while (tmp) {
        if(reevalCounter > MAXIMUM_REEVALUATION){
            printf("\n Error!!! Loop found in formula definition.\n");
            break;
        }
        if (strcmp(tmp->formula,EMPTY_FORMULA) != 0) {
            
            double val = evaluate(tmp->formula, head);
            if(tmp->value != val){
                tmp->value = val;
                tmp=head;
                reevalCounter++;
                continue;
            }              
        }
        tmp = tmp->next;
    }
}
