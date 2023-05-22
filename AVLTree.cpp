#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

struct Node {
  char name[BUFFER_SIZE];
  int age;

  int height;
  Node *left;
  Node *right;
};

Node* createNode(const char *name, int age) {
  Node* newNode = (Node*) malloc(sizeof(Node));
  strncpy(newNode->name, name, BUFFER_SIZE);
  newNode->age = age;
  newNode->height = 1;
  newNode->left = newNode->right = NULL;

  return newNode;
}

int getHeight(Node *node) {
  return node ? node->height : 0; 
}

int max(int a, int b) {
  return a > b ? a : b;
}

void updateHeight(Node *node) {
  if (!node) return;
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBalanceFactor(Node *node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rightRotate(Node *node) {
  Node *newRoot = node->left;
  Node *newRootsOldRight = newRoot->right;

  newRoot->right = node;
  node->left = newRootsOldRight;

  updateHeight(node);
  updateHeight(newRoot);

  return newRoot;
}

Node* leftRotate(Node* node) {
  Node *newRoot = node->right;
  Node *newRootsOldLeft = newRoot->left;

  newRoot->left = node;
  node->right = newRootsOldLeft;

  updateHeight(node);
  updateHeight(newRoot);

  return newRoot;
}

Node* balance(Node *node) {
  int balanceFactor = getBalanceFactor(node);

  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) < -1) node->left = leftRotate(node->left);
    node = rightRotate(node);
  } else if (balanceFactor < -1) {
    if (getBalanceFactor(node->right) > 1) node->right = rightRotate(node->right);
    node = leftRotate(node);
  }

  return node;
}

Node* insert(Node *node, Node *toInsert) {
  if (!node) return toInsert;

  if (toInsert->age < node->age) node->left = insert(node->left, toInsert);
  else node->right = insert(node->right, toInsert);

  updateHeight(node);

  return balance(node);
  // return node;
}

void printTree(Node *node, int depth) {
  if (!node) return;

  printTree(node->left, depth + 1);
  
  for (short i = 0; i < depth * 2; i++) printf(" ");
  printf("%d\n", node->age);

  printTree(node->right, depth + 1);
}

Node* search(Node *node, int age) {
  if (!node) return NULL;

  if (node->age == age) return node;
  else if (age < node->age) return search(node->left, age);
  else return search(node->right, age);
}

void update(Node *root, int ageToUpdate, char *newName) {
  Node* toUpdate = search(root, ageToUpdate);

  if (!toUpdate) printf("Node Not Found");
  else strncpy(toUpdate->name, newName, BUFFER_SIZE);
}

Node* remove(Node* node, int age) {
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

  updateHeight(node);

  return balance(node);
}

int main() {

  Node *root = NULL;
	root = insert(root, createNode("ABC", 10));
	root = insert(root, createNode("DEF", 11));
	root = insert(root, createNode("GHI", 12));
	
	root = remove(root, 12);
	
	printTree(root, 0);

  return 0;
}