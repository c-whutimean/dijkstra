#include "dykstra.h"
#include "ArgumentManager.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>

int numPaths(int src, int dest, multimap<int,int> &paths, unordered_map<int, bool> v){
  typedef multimap<int, int>::iterator MMAPIterator;
  if(src == dest){
    return 1;
  }
  v[src] = true;
  int n = 0;
  pair<MMAPIterator, MMAPIterator> result = paths.equal_range(src);
  for (MMAPIterator it = result.first; it != result.second; it++){
    if(!v[it->second])
      n += numPaths(it->second, dest, paths, v);
  }
  return n;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string inputFileName = am.get("input");
  string outputFileName  = am.get("output");
  string pathFileName = am.get("path");
  ofstream out(outputFileName);
  ifstream in(inputFileName);
  ifstream pth(pathFileName);

  vector<int> x;
  vector<int> y;
  vector<double> len;
  
  string line;
  int n;
  while(getline(in, line)){
    int intVal1, intVal2;
    string strVal1, strVal2, strDistance;
    int pos = line.find(" ");
    strVal1 = line.substr(0, pos+1);
    intVal1 = stoi(strVal1);
    line = line.substr(pos+1);
    pos = line.find(" ");
    strVal2 = line.substr(0, pos+1);
    intVal2 = stoi(strVal2);
    line = line.substr(pos+1);
    strDistance = line;
    double distance = stod(strDistance);
 
    x.push_back(intVal1);
    y.push_back(intVal2);
    len.push_back(distance);
  }
  int size = (*max_element(x.begin(), x.end())) + 1;
 
  int src;
  int dst;
  int i = 0;
  
  while (!pth.eof()) {
    pth >> src >> dst;
  }
  
  Graph g(size);
  for(int i = 0; i < size; i++){
    g.addEdge(x[i], y[i], len[i]);
  }

  g.shortestPath(src, dst, out);
  g.longestPath(src, dst, out);

  multimap<int, int> paths;
  for(int j = 0; j < size; j++){
    paths.insert(make_pair(x[j], y[j]));
  }

  unordered_map<int, bool> nodes;
  for(int k = 0; k < size; k++){
    nodes.insert(make_pair(x[k], false));
  }

  out << numPaths(src, dst, paths, nodes) << endl;

  return 0;
}