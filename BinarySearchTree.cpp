#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

struct Node {
  char name[BUFFER_SIZE];
  int age;

  Node *left;
  Node *right;
};

Node *createNode(const char *name, int age) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  strncpy(newNode->name, name, BUFFER_SIZE);
  newNode->age = age;
  newNode->left = newNode->right = NULL;

  return newNode;
}

Node *insert(Node *node, Node *toInsert) {
  if (!node) return toInsert;

  if (toInsert->age < node->age) node->left = insert(node->left, toInsert);
  else node->right = insert(node->right, toInsert);

  return node;
}

void printTree(Node *node, int depth) {
  if (!node) return;

  printTree(node->left, depth + 1);
  
  for (short i = 0; i < depth * 2; i++) printf(" ");
  printf("%d\n", node->age);

  printTree(node->right, depth + 1);
}

void preOrderTraversal(Node *node) {
  if (!node) return;

  printf("%s - %d\n", node->name, node->age);
  preOrderTraversal(node->left);
  preOrderTraversal(node->right);
}

void inOrderTraversal(Node *node) {
  if (!node) return;

  inOrderTraversal(node->left);
  printf("%s - %d\n", node->name, node->age);
  inOrderTraversal(node->right);
}

void postOrderTraversal(Node *node) {
  if (!node) return;

  postOrderTraversal(node->left);
  postOrderTraversal(node->right);
  printf("%s - %d\n", node->name, node->age);
}

Node *search(Node *node, int age) {
  if (!node) return NULL;

  if (node->age == age) return node;
  else if (age < node->age) return search(node->left, age);
  else return search(node->right, age);
}

void update(Node *root, int ageToUpdate, char *newName) {
  Node *toUpdate = search(root, ageToUpdate);

  if (!toUpdate) printf("Node Not Found");
  else strncpy(toUpdate->name, newName, BUFFER_SIZE);
}

Node *remove(Node *node, int age) {
  if (!node) return NULL;

  if (age < node->age) node->left = remove(node->left, age);
  else if (age > node->age) node->right = remove(node->right, age);
  else {
    if (node->left == NULL && node->right == NULL) {
      free(node);
      node = NULL;
    } else if (node->right && !node->left || !node->right && node->left) {
      free(node);
      node = node->left ? node->left : node->right;
    } else {
      Node *sucessor = node->left;
      while (sucessor->right) sucessor = sucessor->right;

      node->age = sucessor->age;

      node->left = remove(node->left, sucessor->age);
    }
  }

  return node;
}

int main() {
  Node *root = NULL;
  root = insert(root, createNode("ASD", 10));
  root = insert(root, createNode("ASD", 20));
  root = insert(root, createNode("ASD", 30));

  printTree(root, 0);
  return 0;
}