#ifdef NODE_H
#define NODE_H

struct Node{
    int data;
    struct Node* next;
};

struct Node* builOneTwoThree();

int length(struct Node*);

int count(struct Node*, int);

void getNth(struct Node*, int);

void deleteList(struct Node**);

#endif
