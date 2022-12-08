#include "dykstra.h"
#include "adjListNode.h"

Graph::Graph(int V){
  this->V = V;
  this->adj = new list<AdjListNode>[V];
  this->visited = new bool[V];
}

Graph::~Graph(){
  delete [] adj;
}

void Graph::addEdge(int u, int v, double weight){
  AdjListNode node(v, weight);
  adj[u].push_back(node);
}

void Graph::sort(int v, bool visited[]){
  int n = 0;
  visited[v] = true;
  list<AdjListNode>::iterator i;
  
  for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    AdjListNode node = *i;
    if (!visited[node.getV()] && i->getWeight()){
      sort(node.getV(), visited);
    }
  }
  st.push(v);
}

void Graph::filler(){
  for(int i = 0; i < V; i++){
    visited[i] = false;
  }
}

void Graph::shortestPath(int s, int d, ofstream &out){
  double dist[V];
  filler();
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      sort(i, visited);
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX;  // INF
  dist[s] = 0;
  while (st.empty() == false){
    int u = st.top();
    st.pop();
    updateDistances(dist, u, INT_MAX);
  }
  printPathShort(d, dist, out);
  //delete [] visited;
}

void Graph::printPathShort(int dest, double arr[], ofstream &out){
  if (arr[dest] == INT_MAX)  // INF
    out << "Infinite " << endl;
  else
    out << arr[dest] << endl;
}

void Graph::printPathLong(int dest, double arr[], ofstream &out){
  if (arr[dest] == INT_MIN)  // INF
    out << "Infinite " << endl;
  else
    out << arr[dest] << endl;
}

void Graph::longestPath(int s, int d, ofstream &out){
  double dist[V];
  filler();
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      sort(i, visited);
  
  for (int i = 0; i < V; i++)
    dist[i] =  INT_MIN;  // INT_MIN
  dist[s] = 0;
    
  while (st.empty() == false) {
    int u = st.top();
    st.pop();

    updateDistances(dist, u, INT_MIN);
  }
  printPathLong(d, dist, out);
  delete [] visited;
}

void Graph::updateDistances(double dist[], int u, int min_max) {
  list<AdjListNode>::iterator i;

  if (min_max == INT_MIN){
    if (dist[u] != min_max)
      for (i = this->adj[u].begin(); i != this->adj[u].end(); ++i)
        if (dist[i->getV()] < dist[u] + i->getWeight())
          dist[i->getV()] = dist[u] + i->getWeight();
  }
  else if (min_max == INT_MAX)
    if (dist[u] != min_max)
      for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (dist[i->getV()] > dist[u] + i->getWeight())
          dist[i->getV()] = dist[u] + i->getWeight();
}

int Graph::paths(int s, int d, bool* v) {
   if (s == d)
     return 1; 

   visited[s] = true;

   int npaths = 0;
   for (auto i : adj[s]) {
     if (!visited[i.getV()] && i.getWeight()) {
       npaths += paths(i.getV(), d, visited);
     }
   }
  return npaths;
  //delete [] visited;
 }