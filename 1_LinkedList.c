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

void popHead(){

    if (Head == Tail){
    
        free(Head);
        Head = Tail = NULL;
    
    } else {

        Node* toDelete = Head;
        Head = Head->next;
        free(toDelete);
        toDelete = NULL;

    }

}

void popTail(){

    if (Head == Tail){

        free(Head);
        Head = Tail = NULL;

    } else {

        Node* current = Head;
        while (current->next != Tail) current = current->next;
        Tail = current;
        free(current->next);
        current->next = NULL;

    }

}

void pop(int toPop){

    if (!Head) return;
    if (Head->data == toPop) popHead();
    else {

        Node* current = Head;
        while (current->next && current->next->data != toPop) current = current->next;
        
        if (current != Tail){
            
            Node* toDelete = current->next;
            current->next = current->next->next;
            free(toDelete);
            toDelete = NULL;

        }

    }

}

Node* search(int toSearch){

    Node *current = Head;
    while (current && current->data != toSearch) current = current->next;
    return current;

}

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