#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 255
#define TABLESIZE 5

struct Node{

  char name[BUFFERSIZE];
  int age;

  Node* next;
  Node* prev;

};
Node* HEADS[TABLESIZE];
Node* TAILS[TABLESIZE];

Node* createNode(char name[], int age){

  Node* newNode = (Node*) malloc(sizeof(Node));

  strcpy(newNode->name, name);
  newNode->age = age;
  newNode->next = newNode->prev = NULL;

  return newNode;

}

void initiateTable(){

  for (int i = 0; i < TABLESIZE; i++) HEADS[i] = NULL;

}

int hash(char toHash[]){

  int length = strlen(toHash), result = 0;
  for (int i = 0; i < length; i++) result += toHash[i];
  
  return result % TABLESIZE; 

}

// Search
Node* searchByName(char name[]){

  int index = hash(name);

  for (Node* current = HEADS[index]; current; current = current->next)
    if (strcmp(current->name, name) == 0) return current;

  return NULL;

}

// Create
void insert(const char name[], int age){

  int index = hash((char *) name);

  Node* newNode = createNode((char *) name, age);
  if (!HEADS[index]) HEADS[index] = TAILS[index] = newNode;
  else {

    TAILS[index]->next = newNode;
    newNode->prev = TAILS[index];
    TAILS[index] = newNode;

  }

}

// Read
void printTable(){

  for (int i = 0; i < TABLESIZE; i++){

    printf("Index: %d\n", i);

    Node* current = HEADS[i];
    while (current){

      printf("%s %d -> ", current->name, current->age);
      current = current->next;

    }
    
    printf("\n\n");

  }

}

// Update
void update(const char name[], int age){

  Node* toUpdate = searchByName((char *) name);
  if (toUpdate) toUpdate->age = age;

}

// Delete
void deleteNode(const char name[]){

  Node* toDelete = searchByName((char *) name);
  
  if (!toDelete) return;

  int index = hash((char *) name);

  if (toDelete == HEADS[index] && toDelete == TAILS[index]){

    free(HEADS[index]);
    HEADS[index] = TAILS[index] = NULL;

  } else if (toDelete == HEADS[index]){

    HEADS[index] = HEADS[index]->next;
    free(HEADS[index]->prev);
    HEADS[index]->prev = NULL; 

  } else if (toDelete == TAILS[index]){

    TAILS[index] = TAILS[index]->prev;
    free(TAILS[index]->next);
    TAILS[index]->next = NULL;

  } else {

    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    free(toDelete);
    toDelete = NULL;

  }

}

int main(){

  initiateTable();

  insert("ABC", 10);
  insert("ACB", 10);
  insert("BAC", 10);
  insert("BCA", 10);
  insert("CAB", 10);
  insert("CBA", 10);

  printTable();

  return 0;
}