#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node* BuildOneTwoThree(){
    struct Node*  head = malloc(sizeof(struct Node));
    head->data = 1;

    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;

    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 3;

    head->next->next->next = NULL;

    return head;
}

int length(struct Node* head){
    int count = 0;

    struct Node* curr = head;
    while(curr){
        count++;
        curr = curr->next;
    }
    return count;
}

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

int getNth(struct Node* head, int idx){
    /*assert(head != NULL && idx >= 0 && idx < length(head)); //RESUELVES EL CASO EXTREMO :C
    struct Node* curr = head;
    for (int i = 0; i < idx; ++i){
        curr = curr->next;
    }
    return curr->data;*/
    assert(idx >= 0);
    struct Node* curr = head;
    int count = 0;
    while(curr){
        if (idx == count)
            return curr->data;
        count++;
        curr = curr->next;
    }
    assert(0);
    return -1;
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

void push(struct Node** headRef, int data){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    assert(newNode != NULL);

    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;

}

int pop(struct Node** headRef){
    assert(headRef != NULL && *headRef != NULL); // ESTA VACIA?

    struct Node* topNode = *headRef;
    int result = topNode->data;
    *headRef = topNode->next;
    free(topNode);

    return result;
}


void insertNth(struct Node** headRef, int index, int data){
    /*assert(index >= 0 && index <= length(*headRef));
    if (index == 0)
        push(headRef, data);
    else{
        struct Node* curr = *headRef;
        for(int i = 0; i < index - 1; ++i)
            curr = curr->next;
        push(&(curr->next), data);
    }*/
    assert(headRef != NULL && index >= 0);
    if (index == 0){
        push(headRef, data);
        return;
    }

    struct Node* curr = *headRef;
    for (int i = 0; i < index - 1; ++i){
        assert(curr != NULL);
        curr = curr->next;
    }
    assert(curr != NULL);
    push(&(curr->next), data);
}

void append(struct Node** aRef, struct Node** bRef){
    assert(aRef != NULL && bRef != NULL);

    if (*aRef == NULL)
        *aRef = *bRef;
    else{
        struct Node* curr = *aRef;
        while(curr->next)
            curr = curr->next;
        curr->next = *bRef;
    }
    *bRef = NULL;
}
