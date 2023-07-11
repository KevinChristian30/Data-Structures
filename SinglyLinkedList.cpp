#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;

  Node *next;
};

Node *Head = NULL;
Node *Tail = NULL;

Node *createNode(Node node) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->data = node.data;
  newNode->next = NULL;
  
  return newNode;
}

void pushHead(Node toInsert) {
  Node *newNode = createNode(toInsert);
  
  if (!Head) Head = Tail = newNode;
  else {
    newNode->next = Head;
    Head = newNode;
  }
}

void pushTail(Node toInsert) {
  Node *newNode = createNode(toInsert);

  if (!Head) Head = Tail = newNode;
  else {
    Tail->next = newNode;
    Tail = newNode;
  }
}

void pushPriority(Node toInsert) {
  if (!Head || toInsert.data < Head->data) pushHead(toInsert);
  else if (toInsert.data > Tail->data) pushTail(toInsert);
  else {
    Node *newNode = createNode(toInsert), *current;

    for (current = Head; current; current = current->next) 
      if (newNode->data > current->data) break;
    
    newNode->next = current->next;
    current->next = newNode;
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

  Node *toDeallocate = Head;
  Head = Head->next;
  free(toDeallocate);
  toDeallocate = NULL;
}

void popTail() {
  if (!Head) return;

  if (Head == Tail) {
    free(Head);
    Head = Tail = NULL;

    return;
  }

  Node *behindTail;
  for (behindTail = Head; behindTail->next != Tail; behindTail = behindTail->next);

  Tail = behindTail;
  free(Tail->next);
  Tail->next = NULL;
}

void remove(int toRemove) {
  if (!Head) return;

  if (Head->data == toRemove) popHead();
  else if (Tail->data == toRemove) popTail();
  else {
    Node *previousToRemove;
    for (previousToRemove = Head; previousToRemove; previousToRemove = previousToRemove->next)
      if (previousToRemove->next->data == toRemove) break;

    if (!previousToRemove) return;

    Node *toDeallocate = previousToRemove->next;
    previousToRemove->next = previousToRemove->next->next;
    free(toDeallocate);
    toDeallocate = NULL;
  }
}

int main() {
  return 0;
}