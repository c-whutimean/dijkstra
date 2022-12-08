#ifndef DYKSTRA_H
# define DYKSTRA_H

#include <iostream>
#include <limits.h>
#include <climits>
#include <list>
#include <stack>
#include <fstream>
#include "adjListNode.h"

using namespace std;

class Graph {
  int V;
  stack<int> st;
  list<AdjListNode>* adj;
  bool *visited;
  void sort(int v, bool visited[]);

  public:
    Graph(int V);
    ~Graph();

    void addEdge(int u, int v, double weight);
    void longestPath(int s, int d, ofstream &out);
    void shortestPath(int t, int d, ofstream &out);
    void printPathLong(int dest, double arr[], ofstream &out);
    void printPathShort(int dest, double arr[], ofstream &out);
    void filler();
    int paths(int s, int d, bool *v);
    void pathHelperLong(double dist[], int u);
    void pathHelperShort(double dist[], int u);
    void updateDistances(double dist[], int u, int min_max);
};
#endif