#include <stdio.h>

#define HEAP_SIZE 100
#define HEAP_IS_EMPTY 333333

int Heap[HEAP_SIZE];
int NumberOfElementsInHeap = 0;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapifyUp(int currentIndex) {
  if (currentIndex <= 1) return;

  int parentIndex = currentIndex / 2;
  if (Heap[currentIndex] < Heap[parentIndex]) {
    swap(&Heap[currentIndex], &Heap[parentIndex]);

    heapifyUp(parentIndex);
  }
}

void push(int toInsert) {
  Heap[++NumberOfElementsInHeap] = toInsert;

  heapifyUp(NumberOfElementsInHeap);
}

void heapifyDown(int currentIndex) {
  int leftChildIndex = currentIndex * 2;
  int rightChildIndex = leftChildIndex + 1;

  if (rightChildIndex <= NumberOfElementsInHeap) {
    if (Heap[leftChildIndex] >= Heap[currentIndex] && 
        Heap[rightChildIndex] >= Heap[currentIndex]) return;

    int minIndex = Heap[leftChildIndex] < Heap[rightChildIndex] ? 
      leftChildIndex : rightChildIndex;
  
    swap(&Heap[minIndex], &Heap[currentIndex]);
    heapifyDown(minIndex);
  } else if (leftChildIndex <= NumberOfElementsInHeap) {
    if (Heap[leftChildIndex] < Heap[currentIndex]) 
      swap(&Heap[leftChildIndex], &Heap[currentIndex]);
  }
}

void printHeap() {
  for (int i = 1; i <= NumberOfElementsInHeap; i++)
    printf("%d ", Heap[i]);

  puts("");
}

int extractMin() {
  if (NumberOfElementsInHeap == 0) return HEAP_IS_EMPTY;
  if (NumberOfElementsInHeap == 1) return Heap[NumberOfElementsInHeap--];

  int toReturn = Heap[1];

  Heap[1] = Heap[NumberOfElementsInHeap--];
  heapifyDown(1);

  return toReturn;
}

int main() {
  return 0;
}