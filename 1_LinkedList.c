#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

    int data;
    struct Node* next;

} Node;

Node *Head = NULL;
Node *Tail = NULL;

Node* createNode(int toCreate){

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = toCreate;
    newNode->next = NULL;
    return newNode;

}

void pushHead(int toPush){

    Node* newNode = createNode(toPush);
    if (!Head) Head = Tail = newNode;
    else{

        newNode->next = Head;
        Head = newNode;

    }

}

void pushTail(int toPush){

    Node* newNode = createNode(toPush);
    if (!Head) Head = Tail = newNode;
    else {

        Tail->next = newNode;
        Tail = newNode;

    }

}

void pushPriority(int toPush){

    if (!Head) Head = Tail = createNode(toPush);
    else if (toPush < Head->data) pushHead(toPush);
    else if (toPush > Tail->data) pushTail(toPush);
    else {

        Node* current = Head;
        while (current->next->data < toPush) current = current->next;
        Node* newNode = createNode(toPush);
        newNode->next = current->next;
        current->next = newNode;

    }

}

// Pop Head
// Pop Tail
// Pop Middle
// Search

void printLinkedList(){

    Node* current = Head;
    while(current){
        printf("%d -> ", current->data);
        current = current->next;
    }
    puts("");

}

int main(){
    return 0;
}