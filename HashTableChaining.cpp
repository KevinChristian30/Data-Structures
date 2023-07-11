#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 255
#define TABLESIZE 5

struct Node{
  char name[BUFFERSIZE];
  int age;

  Node *next;
  Node *prev;
};

Node *Heads[TABLESIZE];
Node *Tails[TABLESIZE];

Node *createNode(char name[], int age){
  Node *newNode = (Node *) malloc(sizeof(Node));

  strcpy(newNode->name, name);
  newNode->age = age;
  newNode->next = newNode->prev = NULL;

  return newNode;
}

void initiateTable(){
  for (int i = 0; i < TABLESIZE; i++) 
    Heads[i] = NULL;
}

int hash(char toHash[]){
  int length = strlen(toHash), result = 0;
  for (int i = 0; i < length; i++) result += toHash[i];
  
  return result % TABLESIZE; 
}

Node *searchByName(char name[]){
  int index = hash(name);

  for (Node *current = Heads[index]; current; current = current->next)
    if (strcmp(current->name, name) == 0) return current;

  return NULL;
}

void insert(const char name[], int age){
  int index = hash((char *) name);

  Node *newNode = createNode((char *) name, age);
  if (!Heads[index]) Heads[index] = Tails[index] = newNode;
  else {
    Tails[index]->next = newNode;
    newNode->prev = Tails[index];
    Tails[index] = newNode;
  }
}

void printTable(){
  for (int i = 0; i < TABLESIZE; i++){
    printf("Index: %d\n", i);

    for (Node *current = Heads[i]; current; current = current->next)
      printf("%s %d -> ", current->name, current->age);
    
    printf("\n\n");
  }
}

void update(const char name[], int age){
  Node *toUpdate = searchByName((char *) name);
  if (toUpdate) toUpdate->age = age;
}

void deleteNode(const char name[]){
  Node *toDelete = searchByName((char *) name);
  
  if (!toDelete) return;

  int index = hash((char *) name);

  if (toDelete == Heads[index] && toDelete == Tails[index]){
    free(Heads[index]);
    Heads[index] = Tails[index] = NULL;
  } else if (toDelete == Heads[index]){
    Heads[index] = Heads[index]->next;
    free(Heads[index]->prev);
    Heads[index]->prev = NULL; 
  } else if (toDelete == Tails[index]){
    Tails[index] = Tails[index]->prev;
    free(Tails[index]->next);
    Tails[index]->next = NULL;
  } else {
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    free(toDelete);
    toDelete = NULL;
  }
}

int main(){
  return 0;
}