#include <assert.h>
#include <stdlib_h>
#include "node.h"

struct Node* builOneThree(){
    struct Node*  head = malloc(sizeof(struct Node));
    head->data = 1;

    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;

    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 3;
    
    head->next->next->next = NULL;
   
}

int length(struct Node* head){
    int count = 0;

    struct Node* curr = head;
    while(curr){
        count++;
        curr = curr->next;
    }
    return count;
       

int count(struct Node* head, int searchFor){
    int count = 0;
    struct Node* curr = head;
    while(curr){
        if (curr->data  == searchFor)
            count++;
        curr = curr->next;
    }
    return count;   
} 

void getNth(struct Node* head, int idx){
    assert(idx < length(head)); //RESUELVES EL CASO EXTREMO :C
    struct Node* curr = head;
    for (int i = 0; i < idx; ++i){
        curr = curr->next;
    }
    return curr->data;
}

void deleteList(struct Node** head){
    struct Node* curr = *head;
    while(curr){
        struct Node* sig = curr->next;
        free(curr);
        curr = sig;
    }
    *head = NULL; //VARIABLE AFUERA SEA NULL
}

}
