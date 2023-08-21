#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;

  Node *next;
  Node *prev;
};

Node *Head = NULL;
Node *Tail = NULL;

Node *createNode(Node node) {
  Node *newNode = (Node*) malloc(sizeof(Node));
  
  newNode->data = node.data;
  newNode->next = newNode->prev = NULL;
  
  return newNode;
}

void pushHead(Node toInsert) {
  Node *newNode = createNode(toInsert);

  if (!Head) Head = Tail = newNode;
  else {
    newNode->next = Head;
    Head->prev = newNode;
    Head = newNode;
  }
}

void pushTail(Node toInsert) {
  Node *newNode = createNode(toInsert);
  
  if (!Head) Head = Tail = newNode;
  else {
    Tail->next = newNode;
    newNode->prev = Tail;
    Tail = newNode;
  }
}

void pushPriority(Node toInsert) {
  if (!Head || toInsert.data < Head->data) pushHead(toInsert);
  else if (toInsert.data > Tail->data) pushTail(toInsert);
  else {
    Node *newNode = createNode(toInsert), *current;
    for (current = Head; current; current = current->next) 
      if (newNode->data < current->data) break;

    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
  }
}

void printLinkedList() {
  for (Node *current = Head; current; current = current->next) 
    printf("%d -> ", current->data);

  printf("DONE\n");
}

Node *search(int toSearch) {
  for (Node *current = Head; current; current = current->next)
    if (current->data == toSearch) return current;

  return NULL;
}

void update(int oldData, int newData) {
  Node *toUpdate = search(oldData);
  
  if (toUpdate) toUpdate->data = newData;
}

void popHead() {
  if (!Head) return;

  if (Head == Tail) {
    free(Head);
    Head = Tail = NULL;

    return;
  }

  Head = Head->next;
  free(Head->prev);
  Head->prev = NULL;
}

void popTail() {
  if (!Head) return;

  if (Head == Tail){
    free(Head);
    Head = Tail = NULL;

    return;
  }

  Tail = Tail->prev;
  free(Tail->next);
  Tail->next = NULL;
}

void remove(int toRemove) {
  if (!Head) return;

  if (Head == Tail){
    free(Head);
    Head = Tail = NULL;

    return;
  }

  if (Head->data == toRemove) popHead();
  else if (Tail->data == toRemove) popTail();
  else {
    Node *current;
    for (current = Head->next; current; current = current->next)
      if (current->data == toRemove) break;

    if (!current) return;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    current = NULL;
  }
}

int main() {  
  return 0;
}