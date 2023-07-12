#include <stdio.h>
#include <stdlib.h>

struct Edge {
  int sourceIndex;
  int destinationIndex;
};

struct Graph {
  int numberOfVertices;
  int numberOfEdges;
  Edge *edges;
};

Graph createGraph(int numberOfVertices, int numberOfEdges) {
  Graph newGraph = { numberOfVertices, numberOfEdges, NULL };
  newGraph.edges = (Edge *) malloc(numberOfEdges * sizeof(Edge));

  return newGraph;
}

int main() {
  return 0;
}