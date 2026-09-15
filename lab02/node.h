#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    struct Node* next;
};

int length(struct Node* head);
void push(struct Node** headRef, int data);
struct Node* BuildOneTwoThree(void);

int count(struct Node* head, int value);
int getNth(struct Node* head, int index);
void deleteList(struct Node** headRef);
int pop(struct Node** headRef);
void insertNth(struct Node** headRef, int index, int data);
void append(struct Node** aRef, struct Node** bRef);

#endif
