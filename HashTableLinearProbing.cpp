#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 255
#define TABLESIZE 10

struct Node{
  char name[BUFFERSIZE];
  int age;
};
Node HASHTABLE[TABLESIZE];

void initiateTable(){
  for (int i = 0; i < TABLESIZE; i++){
    strcpy(HASHTABLE[i].name, "");
    HASHTABLE[i].age = -1;
  }
}

int hash(char toHash[]){
  int result = 0;
  size_t length = strlen(toHash);
  
  for (size_t i = 0; i < length; i++) result += toHash[i];

  return result % TABLESIZE;
}

int findEmptyIndex(char toFind[]){
  int index = hash((char *) toFind);
  if (HASHTABLE[index].age == -1) return index;

  for (int i = index + 1; i != index; i = (i + 1) % TABLESIZE)
    if (HASHTABLE[i].age == -1) return i;
    
  return -1;
}

int findIndexByName(char toFind[]){
  int index = hash((char *) toFind);
  if (strcmp(HASHTABLE[index].name, toFind) == 0) return index;
    
  for (int i = index + 1; i != index; i = (i + 1) % TABLESIZE)
    if (strcmp(HASHTABLE[i].name, toFind) == 0) return i;

  return -1;
}

void insert(const char name[], int age){
  int index = findEmptyIndex((char *) name);

  if (index == -1) puts("Hash Table Full");
  else {
    strcpy(HASHTABLE[index].name, name);
    HASHTABLE[index].age = age;
  }
}

void printTable(){
  for (int i = 0; i < TABLESIZE; i++)
    printf("%-3d | %-20s %-3d\n", i, HASHTABLE[i].name, HASHTABLE[i].age);
}

void update(const char name[], int age){
  int index = findIndexByName((char *) name);

  if (index == -1) puts("Name Not Found");
  else HASHTABLE[index].age = age;
}

void removeNode(const char name[]){
  int index = findIndexByName((char *) name);

  if (index == -1) puts("Name Not Found");
  else {
    strcpy(HASHTABLE[index].name, "");
    HASHTABLE[index].age = -1;
  }
}

int main(){
  return 0;
}