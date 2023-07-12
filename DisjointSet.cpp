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

int *makeSet(Graph graph) {
  int *parents = (int *) malloc(graph.numberOfVertices * sizeof(int));

  for (int i = 0; i < graph.numberOfVertices; i++) parents[i] = i;

  return parents;
}

int find(int *parents, int toFind) {
  if (parents[toFind] == toFind) return toFind;
  return parents[toFind] = find(parents, parents[toFind]);
}

void _union(int *parents, int sourceParent, int destinationParent) {
  parents[sourceParent] = destinationParent;
}

bool isCyclic(Graph graph) {
  int *parents = makeSet(graph);

  for (int i = 0; i < graph.numberOfEdges; i++) {
    int sourceIndex = graph.edges[i].sourceIndex;
    int destinationIndex = graph.edges[i].destinationIndex;

    int sourceParent = find(parents, sourceIndex);
    int destinationParent = find(parents, destinationIndex);

    if (sourceParent == destinationParent) return true;

    _union(parents, sourceParent, destinationParent);
  }

  free(parents);

  return false;
}

int main() {
  return 0;
}